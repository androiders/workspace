/*
 * utils.c
 *
 *  Created on: 17 sep 2014
 *      Author: packard bell
 */

#include "buttons.h"
#include "lcd.h"

uint8_t getUserValueWithString(const char * str, uint8_t max, uint8_t min, uint8_t delta)
{
	BOOL done = FALSE;
	uint8_t val;
	while( !done )
	{
		uint8_t btn = readButtons();
		printStringAndNum(str,val);
		switch( btn )
		{
		case BTN_UP:
			val += delta;
			break;
		case BTN_DOWN:
			val -= delta;
			break;
		case BTN_OK:
			done = 1;
			break;
		default:
			break;
		}

		if(val > max)
			val = min;
		if(val < min)
			val = max;
	}

	return val;
}

int8_t getValueFromInput()
{
	uint8_t btn = readButtons();
	uint8_t val = -99;
	switch( btn )
	{
	case BTN_UP:
		val = 1;
		break;
	case BTN_DOWN:
		val = -1;
		break;
	case BTN_OK:
		val = 0;
		break;
	default:
		break;
	}

	return val;
}

void printStringAndNum(const char * str, uint8_t tmp)
{
	lcd_gotoxy(0,0);
	lcd_puts(str);
	lcd_gotoxy(0,1);
	lcd_put_num(tmp);
}
