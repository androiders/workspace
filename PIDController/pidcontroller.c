/*
 * pidcontroller.c
 *
 *  Created on: 16 nov 2013
 *      Author: androiders
 */
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "lcd.h"
#include "ds12887.h"
#include "onewire.h"
#include "ds18x20.h"
#include <util/delay.h>
#include <avr/interrupt.h>

//inputs
#define OK PD0
#define UP PD1
#define DOWN PD2

#define MAXSENSORS 5
//outputs
#define MASH_HEAT PD4

#define STATE_STARTUP 0
#define STATE_MASH 	  1
#define STATE_BOIL    2

uint8_t mashTime = 60;
uint8_t mashTemp = 69;
uint8_t initialMashTemp = 73;

uint8_t boilTime = 60;

uint8_t state;

uint8_t gSensorIDs[MAXSENSORS][OW_ROMCODE_SIZE];

volatile uint8_t sec;
volatile uint8_t min;

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

void waitForOk()
{
	while( (PIND & _BV(OK)) == 0);
}

void setMashTimeLoop()
{
	uint8_t done = 0;
	uint8_t input = 0;

	while( !done )
	{
		_delay_ms(200);
		lcd_gotoxy(5,1);
		lcd_put_num(mashTime);
		lcd_puts("    ");
		if(input & _BV(UP))
		{
			mashTime += 10;
		}
		if(input & _BV(DOWN))
		{
			mashTime -= 10;
		}
		if(input & _BV(OK))
		{
			done = 1;
		}
		if(mashTime < 0)
			mashTime = 0;
		if(mashTime > 180)
			mashTime = 180;
		input = PIND;

	}
}


void setMashTempLoop()
{
	uint8_t done = 0;
	uint8_t input = 0;

	while( !done )
	{
		_delay_ms(200);
		lcd_gotoxy(0,1);
		lcd_put_num(mashTemp);
		lcd_putc('(');
		lcd_put_num(initialMashTemp);
		lcd_putc(')');
		if(input & _BV(UP))
		{
			mashTemp += 1;
		}
		if(input & _BV(DOWN))
		{
			mashTemp -= 1;
		}
		if(input & _BV(OK))
		{
			done = 1;
		}
		if(mashTemp < 51)
			mashTemp = 50;
		if(mashTemp >= 99)
			mashTemp = 99;

		initialMashTemp = mashTemp+3;
		input = PIND;

	}
}


static uint8_t search_sensors(void)
{
	uint8_t i;
	uint8_t id[OW_ROMCODE_SIZE];
	uint8_t diff, nSensors;

	ow_reset();

	nSensors = 0;

	diff = OW_SEARCH_FIRST;
	while ( diff != OW_LAST_DEVICE && nSensors < MAXSENSORS ) {
		DS18X20_find_sensor( &diff, &id[0] );

		if( diff == OW_PRESENCE_ERR ) {
			lcd_puts("No Sensor found");
			break;
		}

		if( diff == OW_DATA_ERR ) {
			lcd_puts( "Bus Error");
			break;
		}

		for ( i=0; i < OW_ROMCODE_SIZE; i++ )
			gSensorIDs[nSensors][i] = id[i];

		nSensors++;
	}

	return nSensors;
}

int main(void)
{
	state = STATE_STARTUP;
	sec = 0;
	min = 0;
	//setup PORTD as half input half output
	DDRD = 0xF;
	PORTD &= ~_BV(MASH_HEAT);

	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode

	TIMSK |= (1 << OCIE1A); // Enable CTC interrupt

	sei();

	OCR1A   = 15624; // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64
	TCCR1B |= ((1 << CS10) | (1 << CS11)); // Start timer at Fcpu/64

	lcd_init(LCD_DISP_ON);


//	lcd_puts("connect\n cables!");
//	waitForOk();
//	lcd_clrscr();
//	lcd_puts("set Mash\ntime:");
//	_delay_ms(200);
//	setMashTimeLoop();
//
//	lcd_clrscr();
//	lcd_puts("Mash tmp:");
//	_delay_ms(200);
//	setMashTempLoop();
//
//
//	//switch on ssr for mash tun
//	//ad start mash timer
//
//	lcd_clrscr();
//	lcd_puts("Mash!");
//	state = STATE_MASH;
//
//	PORTD |= _BV(MASH_HEAT);


	uint8_t nSensors, i;
	int16_t decicelsius;
	uint8_t error;


#ifndef OW_ONE_BUS
	ow_set_bus(&PIND,&PORTD,&DDRD,PD6);
#endif

	nSensors = search_sensors();
	lcd_put_num(nSensors);
	lcd_puts(" tmp");

	lcd_gotoxy(0,1);
	if ( DS18X20_get_power_status( &gSensorIDs[i][0] ) == DS18X20_POWER_PARASITE ) {
		lcd_puts("parasite");
	}
	else
	{
		lcd_puts("externally");
	}
	/* clear display and home cursor */
//	lcd_clrscr();8
    _delay_us(100);
	char buf[10];
	uint8_t input = 0x00;
//	ds12887_init();
	while(1)
	{
		_delay_us(10000);
//		lcd_gotoxy(0,1);
		if(DS18X20_start_meas( DS18X20_POWER_EXTERN, NULL ) == DS18X20_OK )
		{
			_delay_ms( DS18B20_TCONV_12BIT );
			i = gSensorIDs[0][0];
			DS18X20_read_decicelsius_single( i, &decicelsius );
			lcd_gotoxy(0,0);
			lcd_puts("temp: ");
			DS18X20_format_from_decicelsius(decicelsius,buf, 10);
			lcd_gotoxy(0,1);
			lcd_put_num(decicelsius);
			lcd_puts("         ");
		}
		else
		{
			lcd_gotoxy(0,1);
			lcd_puts("err");
		}
//		lcd_puts("s: ");
//		lcd_put_num(sec);
//		lcd_gotoxy(0,1);
//		lcd_puts("m: ");
//		lcd_put_num(min);

//		input = PIND;
//		if(input & _BV(OK))
//		{
//			lcd_gotoxy(0,0);
//			lcd_puts("ok");
//		}
//		else
//		{
//			lcd_gotoxy(0,0);
//			lcd_puts("  ");
//		}
//
//		if(input & _BV(UP))
//		{
//			lcd_gotoxy(5,0);
//			lcd_puts("UP");
//		}
//		else
//		{
//			lcd_gotoxy(5,0);
//			lcd_puts("   ");
//
//		}
//		if(input &_BV(DOWN))
//		{
//			lcd_gotoxy(0,1);
//			lcd_puts("DOWN");
//		}
//		else
//		{
//			lcd_gotoxy(0,1);
//			lcd_puts("    ");
//		}

//		uint8_t sec = ds12887_read_sec();
//		itoa(sec,buf,10);
//		lcd_puts(buf);
//		lcd_gotoxy(0,1);
	}

	return 0;
}
