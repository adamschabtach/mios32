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
				display.setMode(seq, Display::OneParameterForSteps);
				display.setParameter(seq, Sequencer::Step::p_noteNumber);
				break;
			case velocities:
			break;
		}
	}
}

