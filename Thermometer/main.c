/*
 * main.c
 *
 *  Created on: 6 okt 2014
 *      Author: androiders
 */

#include <stdio.h>
#include "lcd.h"
#include "onewire.h"
#include "ds18x20.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>

#define MAXSENSORS 1
#define TMP_PIN PD7
#define TMP_PORT PORTD

#define TMP_ROW 1
#define TMP_STR "Temp:"
#define TMP_POS sizeof(TMP_STR)
#define TIME_ROW 0
#define TIME_STR "Time:"
#define TIME_POS sizeof(TIME_STR)

uint8_t gSensorIDs[MAXSENSORS][OW_ROMCODE_SIZE];
int16_t decicelsius;
uint8_t sensorId;
char buf[10];

volatile uint8_t sec;
volatile uint8_t min;
volatile uint8_t test;

void updateTemp(int16_t decicelsius)
{

	DS18X20_format_from_decicelsius(decicelsius,buf,sizeof(buf));
	lcd_gotoxy(TMP_POS,TMP_ROW);
	lcd_puts(buf);
}

void updateTime()
{
	lcd_gotoxy(TIME_POS,TIME_ROW);
	lcd_put_num(min);
	lcd_puts("m ");
	lcd_put_num(sec);
	lcd_puts("s ");
//
}

ISR(TIMER0_COMP_vect)
{
	if(DS18X20_start_meas( DS18X20_POWER_EXTERN, NULL ) == DS18X20_OK )
	{
		DS18X20_read_decicelsius_single( sensorId, &decicelsius );
		updateTemp(decicelsius);
	}
	//test++;
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

	updateTime();
}

//tiemr2 set up as non-inverting fast pwm
//controlls the pump in the system
//initially set to 50% duty cycle
//ISR(TIMER2_COMP_vect)
//{
//	//check if pump value is increased
//	//set new pump value
//	//in output compare register 0
//}



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
//	TCCR2 |= ((1 << WGM21) | (1 << WGM20) | (1 << COM21));
//	//set prescaler to 1024 (frequency is then 1MHz/1024)
//	TCCR2 |= ((1 << CS02) | (1 << CS00));
//	//initially 50% duty
//	OCR2 = 128;
//	//output compare interrupt enable
//	TIMSK |= (1 << OCIE2);

	sei();

}

int main(void)
{
	lcd_init(LCD_DISP_ON);

	lcd_clrscr();
	lcd_gotoxy(0,0);
	search_sensors();

	sensorId = gSensorIDs[0][0];

	lcd_puts("Welcome!");
	_delay_ms(3000);
	lcd_gotoxy(0,1);
	lcd_puts("Initializing");
	_delay_ms(1000);
	lcd_puts(".");
	_delay_ms(1000);
	lcd_puts(".");
	_delay_ms(1000);
	lcd_puts(".");
	_delay_ms(1000);
	lcd_puts(".");
	_delay_ms(1000);


	lcd_clrscr();
	//setup static sreen text:
	lcd_gotoxy(0,TIME_ROW);
	lcd_puts(TIME_STR);
	lcd_gotoxy(0,TMP_ROW);
	lcd_puts(TMP_STR);

	lcd_gotoxy(12,TMP_ROW);
	lcd_putc((char)223);
	lcd_putc('C');

	min = 0;
	sec = 0;

	setupTimers();

	//go to sleep and let interrupts do the rest
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	sleep_enable();
	sleep_mode();
	while(1);

	return 0;
}
