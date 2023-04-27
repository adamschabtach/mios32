/**
 * Editor.h
 * 
 * Code which connects the knobs and buttons to the sequence data and stuff.
 * 
 * Adam Schabtach
 * 4/23/23
 * 
 */

#pragma once

#include "Sequencer.h"
#include "Display.h"

/* These are grabbed from seq_ui.h. */
// TODO find out how to use HWCFG symbols for other buttons.
typedef enum {
  SEQ_UI_BUTTON_GP1,
  SEQ_UI_BUTTON_GP2,
  SEQ_UI_BUTTON_GP3,
  SEQ_UI_BUTTON_GP4,
  SEQ_UI_BUTTON_GP5,
  SEQ_UI_BUTTON_GP6,
  SEQ_UI_BUTTON_GP7,
  SEQ_UI_BUTTON_GP8,
  SEQ_UI_BUTTON_GP9,
  SEQ_UI_BUTTON_GP10,
  SEQ_UI_BUTTON_GP11,
  SEQ_UI_BUTTON_GP12,
  SEQ_UI_BUTTON_GP13,
  SEQ_UI_BUTTON_GP14,
  SEQ_UI_BUTTON_GP15,
  SEQ_UI_BUTTON_GP16,
  SEQ_UI_BUTTON_Exit,
  SEQ_UI_BUTTON_Select,
  SEQ_UI_BUTTON_Left,
  SEQ_UI_BUTTON_Right,
  SEQ_UI_BUTTON_Up,
  SEQ_UI_BUTTON_Down,
  SEQ_UI_BUTTON_Edit  // only used in seq_ui_edit.c
} seq_ui_button_t;


typedef enum {
  SEQ_UI_ENCODER_GP1,
  SEQ_UI_ENCODER_GP2,
  SEQ_UI_ENCODER_GP3,
  SEQ_UI_ENCODER_GP4,
  SEQ_UI_ENCODER_GP5,
  SEQ_UI_ENCODER_GP6,
  SEQ_UI_ENCODER_GP7,
  SEQ_UI_ENCODER_GP8,
  SEQ_UI_ENCODER_GP9,
  SEQ_UI_ENCODER_GP10,
  SEQ_UI_ENCODER_GP11,
  SEQ_UI_ENCODER_GP12,
  SEQ_UI_ENCODER_GP13,
  SEQ_UI_ENCODER_GP14,
  SEQ_UI_ENCODER_GP15,
  SEQ_UI_ENCODER_GP16,
  SEQ_UI_ENCODER_Datawheel
} seq_ui_encoder_t;

class Editor
{
public:

	enum EditModes {
		// The first of these need to match Step::Parameters:
		active = 0,
		noteNumbers,
		velocities,
		gateLengths,
		ccValues,
		probabilities,
		clockMultipliers,
		allStepParams,
		numModes
	};

	Editor();

	/** Do something in response to an encoder change. */
	void handleEncoderChange(Sequencer &seq, int encoder, int delta);

	/** Do something in response to a button change. */
	void handleButtonChange(Sequencer &seq, int button, bool pressed);

	/** Set editing mode. */
	void setMode(Sequencer &seq, EditModes newMode);

	Display display;

private:

	EditModes currentMode;
};