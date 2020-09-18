/*
 * Hysteresis.h
 *
 *  Created on: Nov 29, 2019
 *      Author: androiders
 */

#include <avr/io.h>
#pragma once

class Hysteresis {
public:
	Hysteresis(uint16_t hystVal);
	~Hysteresis() = default;

	uint16_t getValue(uint16_t in);

	void setHysteresisValue(uint16_t hVal);
private:
	uint16_t m_hystValue;
	uint16_t m_currentVale;

};

