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
	Display();

	/** Choose the display mode. */
	void setMode(Modes newMode, Sequence &seq);

	/** Redraw the display. whichStep indicates which step needs to be redrawn;
	 * use -1 to indicate all steps.
	 */
	void update(Sequence &seq, int whichStep = -1);

private:
	enum Modes {
		OneParameterForSteps = 0,
		AllParametersForStep
	};

	Modes currentMode;
	Sequence::Step::Parameters currentParameter;

	/** Display the current parameter for one step in the sequence. */
	void drawStepParameter(Sequence &seq, int whichStep);

	/** Show the given parameter for all steps */
	void showParameterForSteps(Sequence &seq, Sequence::Step::Parameters param);

	/** Show all parameters for one step */
	void showStepParameters(Sequence::Step &step);

};
