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

class Editor
{
public:
	Editor();

	/** Do something in response to an encoder change. */
	void handleEncoderChange(Sequencer &seq, int encoder, int delta);

	/** Do something in response to a button change. */
	void handleButtonChange(Sequencer &seq, int button, bool pressed);

	/** Set editing mode. */
	void setMode(EditMode newMode);
};