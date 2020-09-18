/*
 * Adc.h
 *
 *  Created on: Nov 25, 2019
 *      Author: androiders
 */

#include <avr/io.h>

#pragma once


class Adc {
public:
	Adc();

	~Adc() = default;

	void setVref(uint8_t bitName);
	void setPrescaler(uint8_t flags);
	void enable();

	void setUseInterrupt();
	void clearUseInterrupt();

	uint16_t readOne(uint8_t ADCChannel);

//	void start();
	void startFreeRunning();
private:

//volatile uint8_t * m_port;
//uint8_t m_pin;

volatile uint16_t value;

};

