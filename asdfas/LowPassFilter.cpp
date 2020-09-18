/*
 * LowPassFilter.cpp
 *
 *  Created on: Nov 29, 2019
 *      Author: androiders
 */

#include "LowPassFilter.h"

LowPassFilter::LowPassFilter(uint8_t filterConst)
:m_current(0)
,m_filterConst(filterConst)
{
}


uint16_t LowPassFilter::getValue(uint16_t in)
{
	m_current = (m_current >> 1) + (in >> 2);
	return m_current;

}
