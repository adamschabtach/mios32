/**
 * Editor.cpp
 * 
 * Code which connects the knobs and buttons to the sequence data and stuff.
 * 
 * Adam Schabtach
 * 4/23/23
 * 
 */

#include "Editor.h"
#include "Display.h"
#include "Sequencer.h"

Editor::Editor()
: currentMode(noteNumbers)
{
}

void Editor::handleEncoderChange(Sequencer& seq, int encoder, int delta)
{
	// encoders 0-15 are the general-purpose knobs, 16 is the data wheel
	if (encoder == SEQ_UI_ENCODER_Datawheel) {
		int n = ((int)currentMode + delta + (int)numModes) % (int)numModes;
		EditModes newMode = (EditModes)n;
		setMode(seq, newMode);
	}
}

void Editor::handleButtonChange(Sequencer& seq, int button, bool pressed)
{
	if ((button >= SEQ_UI_BUTTON_GP1) && (button <= SEQ_UI_BUTTON_GP16)) {
		int step = button - SEQ_UI_BUTTON_GP1;
		seq.steps[step].active = !seq.steps[step].active;
		if (currentMode == active) {
			display.update(seq, step, true);
		}
	}
}

void Editor::setMode(Sequencer &seq, EditModes newMode)
{
	if (currentMode != newMode) {
		currentMode = newMode;
		if (newMode != allStepParams) {
			display.setMode(seq, Display::OneParameterForSteps);
			display.setParameter(seq, (Sequencer::Step::Parameters)newMode);
		}
	}
}

