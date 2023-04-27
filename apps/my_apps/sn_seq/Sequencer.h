/** 
 * Sequencer.h
 * 
 * Class declarations for the thing that handles sequence data.
 * 
 * Adam Schabtach
 * 4/21/2023
 * 
 */

#pragma once

#include <stdint.h>
#include <vector>

class Sequencer 
{
public:

	Sequencer();

	class Step
	{
	public:
		Step();

		enum Parameters {
			p_active = 0,
			p_noteNumber,
			p_velocity,
			p_gateLength,
			p_ccValue,
			p_probability,
			p_clockMultiplier,
			numParameters
		};

		bool active;
		int noteNumber;
		int velocity;
		int gateLength;
		int ccValue;
		int probability;
		int clockMultiplier;
	};

	static const int MaxSteps = 16;

	Step steps[MaxSteps];
	int currentStepIndex;
	int sequenceLength;
};
