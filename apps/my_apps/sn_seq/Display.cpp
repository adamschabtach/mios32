/**
 * 	Display.cpp
 * 
 * Routines for putting stuff on the LCD.
 * 
 * Adam Schabtach
 * 4/21/2023
 * 
 */

#pragma once

#include "Display.h"
#include "Sequencer.h"

Display::Display()
: currentMode(OneParameterForSteps),
currentParameter(NoteNumber)
{
}

void Display::setMode(Modes newMode, Sequence &seq)
{
	if (newMode != currentMode) {
		currentMode = newMode;
  		MIOS32_LCD_Clear();
		update(seq);
	}
}

/** Show the given parameter for all steps */
void Display::showParameterForSteps(Sequence &seq, Sequence::Step::Parameters param)
{
}

/** Show all parameters for one step */
void Display::showStepParameters(Sequence::Step &step)
{
}

/** Redraw the display. whichStep indicates which step needs to be redrawn;
 * use -1 to indicate all steps.
 */
void Display::update(Sequence &seq, int whichStep)
{
	switch (currentMode) {
		case OneParameterForSteps:
			if (whichStep == -1) {
				for (int i = 0; i < Sequencer::MaxSteps; i++) {
					drawStepParameter(seq, i);
				}
			} else {
				drawStepParameter(seq, whichStep);
			}
			break;
		case AllParametersForStep:
			showStepParameters(seq[whichStep]);
			break;
	}
}

/** Display the current parameter for one step in the sequence. */
void Display::drawStepParameter(Sequence &seq, int whichStep)
{

}

