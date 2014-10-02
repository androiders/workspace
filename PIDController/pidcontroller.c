/*
 * pidcontroller.c
 *
 *  Created on: 16 nov 2013
 *      Author: androiders
 */

#include <stdio.h>

#include <string.h>
#include <avr/pgmspace.h>
#include "lcd.h"
#include "onewire.h"
#include "ds18x20.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "buttons.h"
#include "mash.h"
//TODO: move to .h file





#define MAXSENSORS 1
#define TMP_PIN PB2
#define TMP_PORT PORTB
//outputs
#define MASH_HEAT PC6

#define STATE_STARTUP 0
#define STATE_MASH 	  1
#define STATE_BOIL    2

//uint16_t mashTime = 60;
//uint16_t mashTemp = 69;
//uint16_t initialMashTemp = 73;

uint8_t boilTime = 60;

uint8_t state;

uint8_t gSensorIDs[MAXSENSORS][OW_ROMCODE_SIZE];
volatile int16_t decicelsius;


volatile uint8_t sec;
volatile uint8_t min;

//heater duty cycle in 10 percent steps
volatile uint8_t heaterPwmDuty = 0;
volatile uint8_t heaterCounter = 0;
//interrupt every 1/10 second
//controlls PID sampling and heater
//heater will use a 2 sec period PWM cycle with
//10% duty intervalls.
ISR(TIMER0_COMP_vect)
{
	//sample PID heat value
	//if( 1 == DS18X20_conversion_in_progress(void) )
	//continue
	//else
//	{
//		uint8_t DS18X20_read_decicelsius( gSensorIDs[0],&decicelsius );
//		DS18X20_start_meas( DS18X20_POWER_EXTERN, NULL );// == DS18X20_OK
//	}
	//samplePid();
	//compare with wanted value
	//adjust heater pwm duty cycle

	//count seconds and store minutes
	heaterCounter++;
//	if(heaterCounter > heaterPwmDuty)
//	{
//		heaterOff();
//	}
//	if(heaterCounter <= heaterPwmDuty)
//	{
//		heaterOn();
//	}
	if( heaterCounter > 20 )
	{
		heaterCounter = 0;
	}

}


//timer1 set up as 1 sec clock
ISR(TIMER1_COMPA_vect)
{
	//count seconds and store minutes
	sec++;
	if( sec > 59 )
	{
		min++;
		sec = 0;
	}
}

//tiemr2 set up as non-inverting fast pwm
//controlls the pump in the system
//initially set to 50% duty cycle
ISR(TIMER2_COMP_vect)
{
	//check if pump value is increased
	//set new pump value
	//in output compare register 0
}



//static uint8_t search_sensors(void)
//{
//	uint8_t i;
//	uint8_t id[OW_ROMCODE_SIZE];
//	uint8_t diff, nSensors;
//
//	ow_reset();
//
//	nSensors = 0;
//
//	diff = OW_SEARCH_FIRST;
//	while ( diff != OW_LAST_DEVICE && nSensors < MAXSENSORS ) {
//		DS18X20_find_sensor( &diff, &id[0] );
//
//		if( diff == OW_PRESENCE_ERR ) {
//			lcd_puts("No Sensor found");
//			break;
//		}
//
//		if( diff == OW_DATA_ERR ) {
//			lcd_puts( "Bus Error");
//			break;
//		}
//
//		for ( i=0; i < OW_ROMCODE_SIZE; i++ )
//			gSensorIDs[nSensors][i] = id[i];
//
//		nSensors++;
//	}
//
//	return nSensors;
//}

void turn_on_mash_heater()
{
	PORTC |= _BV(MASH_HEAT);

}


void turn_off_mash_heater()
{
	PORTC &= ~_BV(MASH_HEAT);
}


void setupTimers()
{
	//set up timer 0 to interrupt every 1/10 second
	//it will be used for PID sampling and heater controll

	//ctc mode with 1024 prescaler
	TCCR0 |= (1 <<WGM01) | (1 << CS02) | (1 << CS00);
	OCR0 = 97;
	TIMSK |= (1 << OCIE0);


	// Configure timer 1 for CTC mode
	TCCR1B |= (1 << WGM12);
	// Enable CTC interrupt
	TIMSK |= (1 << OCIE1A);
	// Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64
	OCR1A   = 15624;
	// Start timer at Fcpu/64
	TCCR1B |= ((1 << CS10) | (1 << CS11));

	//set non-invertin fast PWM mode for timer 2
	//this will controll the pump
	TCCR2 |= ((1 << WGM21) | (1 << WGM20) | (1 << COM21));
	//set prescaler to 1024 (frequency is then 1MHz/1024)
	TCCR2 |= ((1 << CS02) | (1 << CS00));
	//initially 50% duty
	OCR2 = 128;
	//output compare interrupt enable
	TIMSK |= (1 << OCIE2);

	sei();

}

int main(void)
{

	state = STATE_STARTUP;
	sec = 0;
	min = 0;
	//setup PORTD as half input half output
	DDRD = 0xF;


	DDRC = 0xFF;
	//PORTC &= ~_BV(MASH_HEAT);
	PORTC = 0x00;


	lcd_init(LCD_DISP_ON);


	lcd_puts("connect\n cables!");
	waitForOk();
	lcd_clrscr();

	MashProfile profile;
	setupMash(&profile);

//
	lcd_clrscr();

	//switch on ssr for mash tun
	//ad start mash timer
	lcd_clrscr();
	lcd_puts("Starting mash");
	state = STATE_MASH;

//	turn_on_mash_heater();

	uint8_t nSensors, i = 0;

	uint8_t error;


#ifndef OW_ONE_BUS
	ow_set_bus(&PINB,&TMP_PORT,&DDRB,TMP_PIN);
#endif

	uint8_t diff = OW_SEARCH_FIRST;
	if(DS18X20_OK != DS18X20_find_sensor(&diff, gSensorIDs[0]))
	{
		lcd_puts("No Sensor!");
		waitForOk();
		return 1;
	}
//	nSensors = search_sensors();
//	lcd_put_num(nSensors);
//	lcd_puts(" tmp");

	lcd_gotoxy(0,1);
	//DS18X20_get_power_status( &gSensorIDs[i][0] ) == DS18X20_POWER_PARASITE;
//	if ( DS18X20_get_power_status( &gSensorIDs[i][0] ) == DS18X20_POWER_PARASITE )
//	{
//		lcd_puts("parasite");
//	}
//	else
//	{
//		lcd_puts("externally");
//	}
	/* clear display and home cursor */
    _delay_us(100);
	char buf[10];
//	uint8_t input = 0x00;
//	while(1)
//	{
//		_delay_us(1000);
//		if(DS18X20_start_meas( DS18X20_POWER_EXTERN, NULL ) == DS18X20_OK )
//		{
//			_delay_ms( DS18B20_TCONV_12BIT );
//			i = gSensorIDs[0][0];
//			DS18X20_read_decicelsius_single( i, &decicelsius );
//			lcd_clrscr();
//			lcd_gotoxy(0,0);
//			//lcd_puts("t: ");
//			DS18X20_format_from_decicelsius(decicelsius,buf, 10);
//			//lcd_gotoxy(3,0);
//			lcd_puts(buf);
//			lcd_puts(" c");
//			//lcd_put_num(decicelsius);
//			lcd_puts("  ");
//			lcd_gotoxy(1,1);
//			lcd_put_num(min);
//			lcd_puts(":");
//			lcd_put_num(sec);
//			lcd_puts("min");
//		}
//		else
//		{
//			lcd_gotoxy(0,1);
//			lcd_puts("err");
//		}
//
//		//main feedback
//		if(decicelsius < mashTemp * 10)
//		{
//			turn_on_mash_heater();
//		}
////		if(decicelsius < mashTemp)
//		else
//		{
//			turn_off_mash_heater();
//		}
//	}

	return 0;
}
