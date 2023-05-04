// $Id$
/*
 * Local MIOS32 configuration file
 *
 * this file allows to disable (or re-configure) default functions of MIOS32
 * available switches are listed in $MIOS32_PATH/modules/mios32/MIOS32_CONFIG.txt
 *
 */

#ifndef _MIOS32_CONFIG_H
#define _MIOS32_CONFIG_H

// The boot message which is print during startup and returned on a SysEx query
#define MIOS32_LCD_BOOT_MSG_LINE1 "Studio Nebula Sequencer"
#define MIOS32_LCD_BOOT_MSG_LINE2 "(C) 2023 Adam Schabtach"

// function used to output debug messages (must be printf compatible!)
extern void APP_SendDebugMessage(char *format, ...);
#define DEBUG_MSG APP_SendDebugMessage

// Stack size for FreeRTOS tasks as defined by the programming model
// Note that each task maintains it's own stack!
// If you want to define a different stack size for your application tasks

// memory allocated for tasks (observe this with avstack.pl and "memory" terminal command!)
// add +64 for interrupts

// use ./../../bin/avstack.pl  | less
// to doublecheck memory consumption
# define MIOS32_TASK_HOOKS_STACK_SIZE      1000
# define UIP_TASK_STACK_SIZE               1000
# define MIOS32_TASK_MIDI_HOOKS_STACK_SIZE 1400
# define MIDI_TASK_STACK_SIZE              1400
# define PERIOD1MS_TASK_STACK_SIZE         1400
#define PERIOD1MS_LOWPRIO_TASK_STACK_SIZE  1400

// only used by idle task
#define MIOS32_MINIMAL_STACK_SIZE           384
// reserved memory for FreeRTOS pvPortMalloc function
# define MIOS32_HEAP_SIZE 13*1024

// maximum idle counter value to be expected
#define MAX_IDLE_CTR 956000 // STM32F407VG@160 MHz

# define MIOS32_UART_NUM 4

// configure IIC_MIDI
#define MIOS32_IIC_MIDI_NUM 4
// all interfaces are "OUT only"
#define MIOS32_IIC_MIDI0_ENABLED    1
#define MIOS32_IIC_MIDI1_ENABLED    1
#define MIOS32_IIC_MIDI2_ENABLED    1
#define MIOS32_IIC_MIDI3_ENABLED    1
#define MIOS32_IIC_MIDI4_ENABLED    1
#define MIOS32_IIC_MIDI5_ENABLED    1
#define MIOS32_IIC_MIDI6_ENABLED    1
#define MIOS32_IIC_MIDI7_ENABLED    1


// configure BLM driver
#define BLM_DOUT_L1_SR	0
#define BLM_DOUT_R1_SR	0 
#define BLM_DOUT_CATHODES_SR1	0
#define BLM_DOUT_CATHODES_SR2	0
#define BLM_CATHODES_INV_MASK	0x00
#define BLM_DOUT_L2_SR	0
#define BLM_DOUT_R2_SR	0
#define BLM_DOUT_L3_SR	0 // not used
#define BLM_DOUT_R3_SR	0 // not used
#define BLM_DIN_L_SR	0
#define BLM_DIN_R_SR	0
#define BLM_NUM_COLOURS 2
#define BLM_NUM_ROWS    8
#define BLM_DEBOUNCE_MODE 1


// configure BLM_X driver
#define BLM_X_NUM_ROWS            8
#define BLM_X_BTN_NUM_COLS        8
#define BLM_X_LED_NUM_COLS        8
#define BLM_X_LED_NUM_COLORS      1
#define BLM_X_ROWSEL_DOUT_SR      255 // dummy, will be changed in seq_file_hw.c
#define BLM_X_LED_FIRST_DOUT_SR   255 // dummy, will be changed in seq_file_hw.c
#define BLM_X_BTN_FIRST_DIN_SR    255 // dummy, will be changed in seq_file_hw.c
#define BLM_X_ROWSEL_INV_MASK     0   // dummy, will be changed in seq_file_hw.c
#define BLM_X_COL_INV_MASK        0   // dummy, will be changed in seq_file_hw.c
#define BLM_X_DEBOUNCE_MODE       1

// AS not sure if I can just #define this stuff but gotta start somewhere:
// first "A" Matrix: left LeMEC
// to which shift register are the select lines connected?
// Allowed values: 0 to disable, 1..16 to assign shift register
#define BLM8X8_DOUT_CATHODES_SR  3

// set an inversion mask for the DOUT shift registers if sink drivers (transistors)
// have been added to the cathode lines
#define BLM8X8_DOUT_CATHODES_INV_MASK 0xff

// set an inversion mask for the DOUT shift registers if source drivers (transistors)
// have been added to the anode lines
#define BLM8X8_DOUT_ANODES_INV_MASK 0xff

// to which shift register are the LED anode lines connected?
// Allowed values: 0 to disable, 1..16 to assign shift register
#define BLM8X8_DOUT_LED_SR      4

// 0: no mapping of 8x8 LEDs
// 1: select GP LED -> 8x8 matrix mapping for Wilba's MB-SEQ PCB
// 2: select LED mapping for MBSEQ V4L SRIO board
// 3: select GP LED -> matrix mapping for midiphy PCB
#define BLM8X8_DOUT_GP_MAPPING  3

// 8x8 matrix for misc. button functions
#define BLM8X8_DIN_SR  3


// second "B" Matrix: right LeMEC 
#define BLM8X8B_DOUT_CATHODES_SR        8
#define BLM8X8B_DOUT_CATHODES_INV_MASK  0xff
#define BLM8X8B_DOUT_ANODES_INV_MASK    0xff
#define BLM8X8B_DOUT_LED_SR             9
#define BLM8X8B_DIN_SR                  6

// third "C" Matrix, JA PCB
#define BLM8X8C_DOUT_CATHODES_SR        1
#define BLM8X8C_DOUT_CATHODES_INV_MASK  0x00
#define BLM8X8C_DOUT_ANODES_INV_MASK    0x00
#define BLM8X8C_DOUT_LED_SR             2
#define BLM8X8C_DIN_SR                  1


#define BLM8X8_ENABLED  1
#define BLM_BUTTONS_ENABLED 1

#endif /* _MIOS32_CONFIG_H */
