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
		SEQ_LCD_Update(1);
	}
}

/** Set which parameter will be displayed for all steps. */
void Display::setParameter(Sequencer &seq, Sequencer::Step::Parameters param)
{
	static char *names[] = { "Active", "Note", "Velocity", "Gate Length", "CC Value",
		"Probability", "Clock Multiplier" };

	if (param != currentParameter) {
		currentParameter = param;
		SEQ_LCD_Clear();
		SEQ_LCD_CursorSet(0, 0);
		SEQ_LCD_PrintString(names[param]);
		update(seq);
		SEQ_LCD_Update(1);
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
 * use -1 to indicate all steps. If updateNow is true, also send the changes
 * to the LCD.
 */
void Display::update(Sequencer &seq, int whichStep, bool updateNow)
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
			showStepParameters(seq.steps[whichStep]);
			break;
	}
	if (updateNow) {
		SEQ_LCD_Update(0);
	}
}

/** Display the current parameter for one step in the sequence. */
void Display::drawStepParameter(Sequencer &seq, int whichStep)
{
	char str[6];
	SEQ_LCD_CursorSet(5 * whichStep, 1);
	switch (currentParameter) {
		case Sequencer::Step::p_active:
			sprintf(str, "%s", seq.steps[whichStep].active ? "On" : "Off");
			break;
		case Sequencer::Step::p_noteNumber:
			sprintf(str, "%d", seq.steps[whichStep].noteNumber);
			break;
		case Sequencer::Step::p_ccValue:
			sprintf(str, "%d", seq.steps[whichStep].ccValue);
			break;
		case Sequencer::Step::p_velocity:
			sprintf(str, "%d", seq.steps[whichStep].velocity);
			break;
		case Sequencer::Step::p_gateLength:
			sprintf(str, "%d%%", seq.steps[whichStep].gateLength);
			break;
		case Sequencer::Step::p_probability:
			sprintf(str, "%d%%", seq.steps[whichStep].probability);
			break; 
	}
	SEQ_LCD_PrintStringPadded(str, 5);
}

