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

class Sequencer 
{
	public:

	class Step
	{
		public:

		Step();
		~Step();

		bool active;
		uint8_t noteNumber;
		uint8_t velocity;
		uint8_t gateLength;
		uint8_t ccValue;
	};
};
