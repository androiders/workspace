/*
 * RotaryEncoder.cpp
 *
 *  Created on: Nov 20, 2019
 *      Author: androiders
 */

#include "RotaryEncoder.h"

int8_t RotaryEncoder::lookup_table[16] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};


RotaryEncoder::RotaryEncoder(volatile uint8_t * PINPORT, uint8_t pin0, uint8_t pin1)
:mInPort(PINPORT)
,mPin0(pin0)
,mPin1(pin1)
,mEncVal(0)
,mValue(0)
{
}

void RotaryEncoder::calculate()
{
	mEncVal = mEncVal << 2;
	uint8_t bitMask = (*mInPort) & ((1 << mPin0) | (1 << mPin1));
	mEncVal = mEncVal | (bitMask >>2);
	mValue = mValue + lookup_table[mEncVal & 0x0F];
}

uint16_t RotaryEncoder::getValue() const
{
	return mValue;
}
