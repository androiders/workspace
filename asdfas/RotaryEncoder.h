/*
 * RotaryEncoder.h
 *
 *  Created on: Nov 20, 2019
 *      Author: androiders
 */

#include <avr/io.h>

#pragma once

class RotaryEncoder
{
public:
	RotaryEncoder(volatile uint8_t * PORT, uint8_t pin0, uint8_t pin1);
	~RotaryEncoder() = default;

	//can be called from ISR
	void calculate();
	uint16_t getValue() const;
private:

	volatile uint8_t* mInPort;
	uint8_t mPin0;
	uint8_t mPin1;
	volatile int8_t mEncVal;
	volatile uint16_t mValue;

	static int8_t lookup_table[16];// = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
};


