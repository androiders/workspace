/*
 * Adc.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: androiders
 */

#include "Adc.h"

Adc::Adc() {
	// TODO Auto-generated constructor stub
	// Select Vref=AVcc
//	 ADMUX |= (1<<REFS0);
	 //set prescaller to 128 and enable ADC
//	 ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

void Adc::setVref(uint8_t bitName)
{
	ADMUX |= (1<<bitName);
}

void Adc::setPrescaler(uint8_t flags)
{
	//use safety mask!!
	//ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)
	ADCSRA |= flags;
}

void Adc::enable()
{
	ADCSRA |= (1<<ADEN);
}

void Adc::setUseInterrupt()
{
	ADCSRA |= (1 << ADIE);
}

void Adc::clearUseInterrupt()
{
	ADCSRA &= ~(1 << ADIE);
}

uint16_t Adc::readOne(uint8_t ADCChannel)
{
	//select ADC channel with safety mask
	 ADMUX = (ADMUX & 0xF0) | (ADCChannel & 0x0F);
	 //single conversion mode
	 ADCSRA |= (1<<ADSC);
	 // wait until ADC conversion is complete
	 while( ADCSRA & (1<<ADSC) );
	 return ADC;
}

//void Adc::start()
//{
//	AD
//}

void Adc::startFreeRunning()
{

}
