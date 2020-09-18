/*
 * Hysteresis.cpp
 *
 *  Created on: Nov 29, 2019
 *      Author: androiders
 */

#include "Hysteresis.h"

Hysteresis::Hysteresis(uint16_t hystVal)
:m_hystValue(hystVal)
,m_currentVale(0)
{

}

uint16_t Hysteresis::getValue(uint16_t in)
{
	if(in > (m_currentVale + m_hystValue) || in < (m_currentVale - m_hystValue))
		m_currentVale = in;

	return m_currentVale;
}

void Hysteresis::setHysteresisValue(uint16_t hVal)
{
	m_hystValue = hVal;
}
