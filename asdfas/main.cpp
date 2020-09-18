/*
 * main.cpp
 *
 *  Created on: Nov 10, 2019
 *      Author: androiders
 */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "RotaryEncoder.h"
#include "Adc.h"
//#include "LowPassFilter.h"
//#include "Hysteresis.h"
#include "MovingAverage.h"

//int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1000000000000000000,,00,1,-1,0};
volatile int8_t enc_count = 0;
volatile bool change= false;

void toggle()
{
	PORTB ^= (1 << PINB1);
}

RotaryEncoder re(&PINC, PINC2, PINC3);

ISR(PCINT1_vect)
{
	re.calculate();
	change = true;
}

void setupTimer()
{

   // Set on match, clear on TOP
   TCCR1A  = ((1 << COM1A1) | (1 << COM1A0) | (1 << WGM10) | ( 1 << WGM11));

   // Phase Correct PWM, Fcpu speed
   TCCR1B  = (1 << CS10);
}

//ISR(PCINT0_vect)
//{
//
//	inc = PINC;
//	enc_val = enc_val << 2;
//    enc_val = enc_val | ((PINC & 0b00001100)>>2);
//
//    enc_count = enc_count + lookup_table[enc_val & 0x0F];
//    change = true;
//    //toggle();
//}

//ISR(PCINT2_vect)
//{
//
//	inc = PINC;
//	enc_val = enc_val << 2;
//    enc_val = enc_val | ((PINC & 0b00001100)>>2);
//
//    enc_count = enc_count + lookup_table[enc_val & 0x0F];
//    change = true;
//    //toggle();
//}


int main()
{
//	LowPassFilter lpf(4);
//	Hysteresis h(8);
	MovingAverage<7> ma5;
	Adc adc;
	adc.setVref(REFS0);
	adc.setPrescaler((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	adc.enable();

	DDRB |= (1 << PINB1);
	//PORTB = 0xFF;

	DDRC = 0x00;
	PORTC = 0xFF;

	PCICR = (1 << PCIE1);// | (1 << PCIE0) | (1 << PCIE2);//enable PCIE0
	//PCMSK1 = (1 << PCINT10) | (1 << PCINT11);
	//PCMSK0 = 0xFF;
	PCMSK1 = 0x0C;
	//PCMSK2 = 0xFF;
	sei();

	setupTimer();

	lcd_init();
	lcd_on();
	//lcd_enable_autoscroll();
	//lcd_enable_blinking();
	lcd_set_cursor(0,0);
	//lcd_return_home();
	lcd_enable_cursor();
	lcd_set_left_to_right();
	lcd_clear();
	lcd_printf("Hejsan");

	while(true)
	{
//		toggle();
//		lcd_write('a');
		_delay_ms(100);

		//volatile uint16_t adval = h.getValue(adc.readOne(0x00));
//		volatile uint16_t adval = lpf.getValue(adc.readOne(0x00));
		volatile uint16_t adcVal = adc.readOne(0x00);
		volatile uint16_t adval = ma5.getValue(adcVal);
		lcd_return_home();
		lcd_clear();
		lcd_printf("%d, %d",adval,adcVal);

		OCR1A=adval;
//		if(change)
//		{
//			lcd_return_home();
//			lcd_clear();
//			uint16_t v = re.getValue();
//			//lcd_set_cursor(1,1);
//			//lcd_write(enc_count);
//			lcd_printf("%d",v);
//			lcd_set_cursor(1,1);
////			lcd_printf("%d",inc);
//			change = false;
//			toggle();
//		}

	}
	return 0;
}
