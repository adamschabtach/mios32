#include "Sequencer.h"



Sequencer::Step::Step()
: active(true),
noteNumber(60),
velocity(100),
gateLength(50),
ccValue(0),
probability(100),
clockMultiplier(1)
{
}

Sequencer::Sequencer()
: currentStepIndex(0)
{
	sequenceLength = MaxSteps;
	for (int i = 0; i < MaxSteps; i++) {
		steps[i] = Step();
	}
}
