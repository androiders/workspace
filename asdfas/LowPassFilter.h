/*
 * LowPassFilter.h
 *
 *  Created on: Nov 29, 2019
 *      Author: androiders
 */

#pragma once
#include <avr/io.h>

class LowPassFilter {
public:
	LowPassFilter(uint8_t filterConst);
	~LowPassFilter() = default;

	uint16_t getValue(uint16_t in);
private:

	uint16_t m_current;
	uint8_t m_filterConst;
};

