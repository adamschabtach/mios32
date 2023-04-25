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

Editor::Editor()
{
}

void Editor::handleEncoderChange(Sequencer& seq, int encoder, int delta)
{
}

void Editor::handleButtonChange(Sequencer& seq, int button, bool pressed)
{
}

void Editor::setMode(Sequencer &seq, EditModes newMode)
{
	if (currentMode != newMode) {
		currentMode = newMode;
		switch (newMode) {
			case noteNumbers:
				display.setMode(seq, Display::DisplayModes::OneParameterForSteps);
				display.setParameter(seq, Sequencer::Step::Parameters::p_noteNumber);
				break;
			case velocities:
			case gateLengths:
			case ccValues:
			case probabilities:
			case clockMultipliers:
			case allStepParams:
			break;
		}
	}
}

