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
#include <algorithm>

int addToMIDIValue(int &val, int change) {
  return val = std::max<int>(std::min<int>(val + change, 127), 0);
}

int addToPercentValue(int &val, int change) {
  return val = std::max<int>(std::min<int>(val + change, 100), 0);
}

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
	} else {
		if (currentMode == allStepParams) {

		} else {
			int stepNum = encoder;
			switch (currentMode) {
				case noteNumbers:
					addToMIDIValue(seq.steps[stepNum].noteNumber, delta);
					break;
				case velocities:
					addToMIDIValue(seq.steps[stepNum].velocity, delta);
					break;
				case ccValues:
					addToMIDIValue(seq.steps[stepNum].ccValue, delta);
					break;
				case gateLengths:
					addToPercentValue(seq.steps[stepNum].gateLength, delta);
					break;
				case probabilities:
					addToPercentValue(seq.steps[stepNum].probability, delta);
					break;
				case active:
				case clockMultipliers:
					break;
			}
			display.update(seq, stepNum, true);
		}
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

