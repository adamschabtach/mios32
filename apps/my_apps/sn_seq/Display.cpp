/**
 * 	Display.cpp
 * 
 * Routines for putting stuff on the LCD.
 * 
 * Adam Schabtach
 * 4/21/2023
 * 
 */

#include "Display.h"
#include "Sequencer.h"
#include "my_seq_lcd.h"

Display::Display()
: currentMode(OneParameterForSteps),
currentParameter(Sequencer::Step::p_noteNumber)
{
}

void Display::setMode(Sequencer &seq, DisplayModes newMode)
{
	if (newMode != currentMode) {
		currentMode = newMode;
  		SEQ_LCD_Clear();
		update(seq);
	}
}

/** Set which parameter will be displayed for all steps. */
void Display::setParameter(Sequencer &seq, Sequencer::Step::Parameters param)
{
	if (param != currentParameter) {
		currentParameter = param;
		update(seq);
	}
}

/** Show the given parameter for all steps */
void Display::showParameterForSteps(Sequencer &seq, Sequencer::Step::Parameters param)
{
}

/** Show all parameters for one step */
void Display::showStepParameters(Sequencer::Step &step)
{
}

/** Redraw the display. whichStep indicates which step needs to be redrawn;
 * use -1 to indicate all steps.
 */
void Display::update(Sequencer &seq, int whichStep)
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
			showStepParameters(seq.sequence[whichStep]);
			break;
	}
}

/** Display the current parameter for one step in the sequence. */
void Display::drawStepParameter(Sequencer &seq, int whichStep)
{
	int n = -999;
	char str[6];
	SEQ_LCD_CursorSet(5 * whichStep, 1);
	switch (currentParameter) {
		case Sequencer::Step::p_noteNumber:
			n = seq.sequence[whichStep].noteNumber;
			break;
		case Sequencer::Step::p_ccValue:
			n = seq.sequence[whichStep].ccValue;
			break;
		case Sequencer::Step::p_velocity:
			n = seq.sequence[whichStep].velocity;
			break;
		case Sequencer::Step::p_gateLength:
			n = seq.sequence[whichStep].gateLength;
			break;
		case Sequencer::Step::p_probability:
			n = seq.sequence[whichStep].probability;
			break;
	}
	sprintf(str, "%d", n);
	SEQ_LCD_PrintStringPadded(str, 5);
}

