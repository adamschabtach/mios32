// $Id$
/*
 * MIOS32 Tutorial #017: A simple Sequencer
 *
 * ==========================================================================
 *
 *  Copyright (C) 2009 Thorsten Klose (tk@midibox.org)
 *  Licensed for personal non-commercial use only.
 *  All other rights reserved.
 * 
 * ==========================================================================
 */

/////////////////////////////////////////////////////////////////////////////
// Include files
/////////////////////////////////////////////////////////////////////////////

#include <mios32.h>

#include <cstdarg>
#include <cstring>

#include "file.h"
#include <FreeRTOS.h>
#include <portmacro.h>
#include <task.h>

#include <notestack.h>
#include <seq_bpm.h>
#include <seq_midi_out.h>
extern "C" {
#include "../../sequencers/midibox_seq_v4/core/seq_hwcfg.h"
#include "../../sequencers/midibox_seq_v4/core/seq_blm8x8.h"
#include "../../../../modules/blm/blm.h"
}
#include "seq.h"
#include "my_seq_lcd.h"
#include "hwcfg.h"
#include "Display.h"
#include "Editor.h"
#include "Sequencer.h"
#include "app.h"


/////////////////////////////////////////////////////////////////////////////
// Local definitions
/////////////////////////////////////////////////////////////////////////////

#define NOTESTACK_SIZE 16
Sequencer sequencer;
Editor editor;

/////////////////////////////////////////////////////////////////////////////
// Local definitions
/////////////////////////////////////////////////////////////////////////////

#define PRIORITY_TASK_SEQ		( tskIDLE_PRIORITY + 4 ) // higher priority than MIDI receive task!


/////////////////////////////////////////////////////////////////////////////
// Local Prototypes
/////////////////////////////////////////////////////////////////////////////
extern "C" void TASK_SEQ(void *pvParameters);
extern "C" s32 NOTIFY_MIDI_Rx(mios32_midi_port_t port, u8 byte);


/////////////////////////////////////////////////////////////////////////////
// This hook is called after startup to initialize the application
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_Init(void)
{
  // initialize all LEDs
  MIOS32_BOARD_LED_Init(0xffffffff);

  // turn off gate LED
  MIOS32_BOARD_LED_Set(1, 0);

  hwcfg_init();

  SEQ_LCD_Init(0); 
  BLM_Init(0);
  SEQ_BLM8X8_Init(0);

  // initialize MIDI handler
  SEQ_MIDI_OUT_Init(0);

  // initialize sequencer
  SEQ_Init(0);

  // install MIDI Rx callback function
 // MIOS32_MIDI_DirectRxCallback_Init(NOTIFY_MIDI_Rx);

  // install sequencer task
//  xTaskCreate(TASK_SEQ, "SEQ", configMINIMAL_STACK_SIZE, NULL, PRIORITY_TASK_SEQ, NULL);

  editor.setMode(sequencer, Editor::noteNumbers);
  editor.display.update(sequencer, -1, true);  
 #if 0 
  FILE_Init(0);
  s32 status = FILE_CheckSDCard();

  if( status == 1 ) {
      MIOS32_MIDI_SendDebugMessage("SD Card connected: %s\n", FILE_VolumeLabel());
    } else {
      MIOS32_MIDI_SendDebugMessage("No SD Card found.");
    }
#endif
}


/////////////////////////////////////////////////////////////////////////////
// This task is running endless in background
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_Background(void)
{
  /*
  SEQ_LCD_Clear();
  SEQ_LCD_CursorSet(10, 0);
  SEQ_LCD_PrintString("Here at 10,0");
  SEQ_LCD_CursorSet(70, 1);
  SEQ_LCD_PrintString("Here at 70,1");
  SEQ_LCD_Update(1);
  */
/*
    // print system time
    MIOS32_LCD_CursorSet(0, 0); // X, Y
    MIOS32_LCD_PrintFormattedString("System Time");

    MIOS32_LCD_CursorSet(0, 1); // X, Y
    mios32_sys_time_t t = MIOS32_SYS_TimeGet();
    int hours = t.seconds / 3600;
    int minutes = (t.seconds % 3600) / 60;
    int seconds = (t.seconds % 3600) % 60;
    int milliseconds = t.fraction_ms;
    MIOS32_LCD_PrintFormattedString("%02d:%02d:%02d.%03d", hours, minutes, seconds, milliseconds);
*/
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called each mS from the main task which also handles DIN, ENC
// and AIN events. You could add more jobs here, but they shouldn't consume
// more than 300 uS to ensure the responsiveness of buttons, encoders, pots.
// Alternatively you could create a dedicated task for application specific
// jobs as explained in $MIOS32_PATH/apps/tutorials/006_rtos_tasks
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_Tick(void)
{
  // set LED depending on sequencer run state
  MIOS32_BOARD_LED_Set(1, SEQ_BPM_IsRunning() ? 1 : 0);
  BLM_ButtonHandler(APP_BLM_NotifyToggle);
  SEQ_BLM8X8_ButtonHandler(APP_SEQ_BLM8X8_NotifyToggle);
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called each mS from the MIDI task which checks for incoming
// MIDI events. You could add more MIDI related jobs here, but they shouldn't
// consume more than 300 uS to ensure the responsiveness of incoming MIDI.
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_MIDI_Tick(void)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a MIDI package has been received
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_MIDI_NotifyPackage(mios32_midi_port_t port, mios32_midi_package_t midi_package)
{
  // Note On received?
  if( midi_package.chn == Chn1 && 
      (midi_package.type == NoteOn || midi_package.type == NoteOff) ) {

    // branch depending on Note On/Off event
    if( midi_package.event == NoteOn && midi_package.velocity > 0 )
      SEQ_NotifyNoteOn(midi_package.note, midi_package.velocity);
    else
      SEQ_NotifyNoteOff(midi_package.note);
  }
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called before the shift register chain is scanned
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_SRIO_ServicePrepare(void)
{
    // prepare DOUT registers of BLM to drive the column
    BLM_PrepareCol();
    // prepare DOUT registers of 8x8 BLM to drive the row
    SEQ_BLM8X8_PrepareRow();
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called after the shift register chain has been scanned
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_SRIO_ServiceFinish(void)
{
    // call the BL_GetRow function after scan is finished to capture the read DIN values
    BLM_GetRow();
    // call the BL_X_GetRow function after scan is finished to capture the read DIN values
    SEQ_BLM8X8_GetRow();

}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a button has been toggled
// pin_value is 1 when button released, and 0 when button pressed
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_DIN_NotifyToggle(u32 pin, u32 pin_value)
{
    MIOS32_MIDI_SendDebugMessage("Button %d %s\n", pin, pin_value ? "depressed" : "pressed");

  editor.handleButtonChange(sequencer, pin, pin_value);
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when an encoder has been moved
// incrementer is positive when encoder has been turned clockwise, else
// it is negative
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_ENC_NotifyChange(u32 encoder, s32 incrementer)
{
  MIOS32_MIDI_SendDebugMessage("Encoder %d %d\n", encoder, incrementer);
  editor.handleEncoderChange(sequencer, encoder, incrementer);
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a pot has been moved
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_AIN_NotifyChange(u32 pin, u32 pin_value)
{
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a BLM button has been toggled
// (see also SEQ_TASK_Period1mS)
// pin_value is 1 when button released, and 0 when button pressed
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_BLM_NotifyToggle(u32 pin, u32 pin_value)
{
  u8 row = pin / 16;
  u8 pin_of_row = pin % 16;
    MIOS32_MIDI_SendDebugMessage("[DIN_TESTMODE] BLM Pin M%d D%d %s\n", row+1, pin_of_row, pin_value ? "depressed" : "pressed");

  // forward to UI BLM button handler
//  SEQ_UI_BLM_Button_Handler(row, pin_of_row, pin_value);
}


/////////////////////////////////////////////////////////////////////////////
// This hook is called when a SEQ_BLM8X8 button has been toggled
// (see also SEQ_TASK_Period1mS)
// pin_value is 1 when button released, and 0 when button pressed
/////////////////////////////////////////////////////////////////////////////
extern "C" void APP_SEQ_BLM8X8_NotifyToggle(u8 blm, u32 pin, u32 pin_value)
{
    MIOS32_MIDI_SendDebugMessage("[DIN_TESTMODE] BLM8x8 Pin M%d%c D%d %s\n", (pin>>3)+1, 'A'+blm, pin&7, pin_value ? "depressed" : "pressed");
  }

/////////////////////////////////////////////////////////////////////////////
// This task is called periodically each mS to handle sequencer requests
/////////////////////////////////////////////////////////////////////////////
extern "C" void TASK_SEQ(void *pvParameters)
{
  portTickType xLastExecutionTime;

  // Initialise the xLastExecutionTime variable on task entry
  xLastExecutionTime = xTaskGetTickCount();

  while( 1 ) {
    vTaskDelayUntil(&xLastExecutionTime, 1 / portTICK_RATE_MS);

    // execute sequencer handler
    SEQ_Handler();

    // send timestamped MIDI events
    SEQ_MIDI_OUT_Handler();
  }
}

/////////////////////////////////////////////////////////////////////////////
// Installed via MIOS32_MIDI_DirectRxCallback_Init
/////////////////////////////////////////////////////////////////////////////
extern "C" s32 NOTIFY_MIDI_Rx(mios32_midi_port_t port, u8 midi_byte)
{
  // here we could filter a certain port
  // The BPM generator will deliver inaccurate results if MIDI clock 
  // is received from multiple ports
  SEQ_BPM_NotifyMIDIRx(midi_byte);

  return 0; // no error, no filtering
}

/////////////////////////////////////////////////////////////////////////////
// Send a Mutex protected debug messages (referenced by DEBUG_MSG macro)
/////////////////////////////////////////////////////////////////////////////
// AS except that we don't really have mutexes yet...
#define MUTEX_MIDIOUT_TAKE
#define MUTEX_MIDIOUT_GIVE
extern "C" void APP_SendDebugMessage(char *format, ...)
{
  MUTEX_MIDIOUT_TAKE;

  {
    char str[128]; // 128 chars allowed
    va_list args;

    // failsave: if format string is longer than 100 chars, break here
    // note that this is a weak protection: if %s is used, or a lot of other format tokens,
    // the resulting string could still lead to a buffer overflow
    // other the other hand we don't want to allocate too many byte for buffer[] to save stack
    if( strlen(format) > 100 ) {
      // exit with less costly message
      MIOS32_MIDI_SendDebugString("(ERROR: string passed to MIOS32_MIDI_SendDebugMessage() is longer than 100 chars!\n");
    } else {
      // transform formatted string into string
      va_start(args, format);
      vsprintf(str, format, args);
    }

    size_t len = strlen(str);
    u8 *str_ptr = (u8 *)str;
    size_t i;
    for(i=0; i<len; ++i) {
      *str_ptr++ &= 0x7f; // ensure that MIDI protocol won't be violated
    }

    MIOS32_MIDI_SendDebugString(str);
  }

  MUTEX_MIDIOUT_GIVE;
}