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

	enum EditModes {
		noteNumbers = 0,
		velocities,
		gateLengths,
		ccValues,
		probabilities,
		clockMultipliers,
		allStepParams
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