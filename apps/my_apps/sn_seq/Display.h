/**
 * 	Display.h
 * 
 * Routines for putting stuff on the LCD.
 * 
 * Adam Schabtach
 * 4/21/2023
 * 
 */

#pragma once

#include "Sequencer.h"

class Display
{
public:
	enum DisplayModes {
		OneParameterForSteps = 0,
		AllParametersForStep
	};
	Display();

	/** Choose the display mode. */
	void setMode(Sequencer &seq, DisplayModes newMode);

	/** Set which parameter will be displayed for all steps. */
	void setParameter(Sequencer &seq, Sequencer::Step::Parameters param);

	/** Redraw the display. whichStep indicates which step needs to be redrawn;
	 * use -1 to indicate all steps.
	 */
	void update(Sequencer &seq, int whichStep = -1);

private:

	DisplayModes currentMode;
	Sequencer::Step::Parameters currentParameter;

	/** Display the current parameter for one step in the sequence. */
	void drawStepParameter(Sequencer &seq, int whichStep);

	/** Show the given parameter for all steps */
	void showParameterForSteps(Sequencer &seq, Sequencer::Step::Parameters param);

	/** Show all parameters for one step */
	void showStepParameters(Sequencer::Step &step);

};
