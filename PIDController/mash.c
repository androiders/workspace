/*
 * mash.c
 *
 *  Created on: 15 sep 2014
 *      Author: packard bell
 */
#include "buttons.h"
#include "mash.h"

BOOL initMashProfile(MashProfile * profile, MashType type)
{
	if(profile == NULL)
		return FALSE;
	profile->type = type;

	return TRUE;
}

void setNumberOfMashBreaks(MashProfile * profile)
{
	BOOL done = FALSE;
	uint8_t breaks = 2;
	while( !done )
	{
		uint8_t btn = readButtons();
		lcd_gotoxy(5,1);
		lcd_put_num(breaks);
		lcd_puts("    ");
		switch( btn )
		{
		case BTN_UP:
			breaks += 1;
			break;
		case BTN_DOWN:
			breaks -= 1;
			break;
		case BTN_OK:
			done = 1;
			break;
		default:
			break;
		}

		if(breaks < 2)
			breaks = 2;
		if(breaks > MAX_NR_OF_BREAKS)
			breaks = 10;
	}
	profile->nrOfBreaks = breaks;
}

uint8_t setMashTimeLoop()
{
	uint8_t done = 0;
	uint8_t input = 0;

	while( !done )
	{
		uint8_t btn = readButtons();
		lcd_gotoxy(5,1);
		lcd_put_num(mashTime);
		lcd_puts("    ");
		switch( btn )
		{
		case BTN_UP:
			mashTime += 10;
			break;
		case BTN_DOWN:
			mashTime -= 10;
			break;
		case BTN_OK:
			done = 1;
			break;
		default:
			break;
		}

		if(mashTime < 0)
			mashTime = 0;
		if(mashTime > 180)
			mashTime = 180;
	}
	return mashTime;
}

//TODO: remove initialMashTemp!?!?!
uint8_t setMashTempLoop()
{
	uint8_t done = 0;
	uint8_t input = 0;

	while( !done )
	{
		lcd_gotoxy(0,1);
		lcd_put_num(mashTemp);
		lcd_putc('(');
		lcd_put_num(initialMashTemp);
		lcd_putc(')');
		uint8_t btn = readButtons();
		switch( btn )
		{
		case BTN_UP:
			mashTemp += 1;
			break;
		case BTN_DOWN:
			mashTemp -= 1;
			break;
		case BTN_OK:
			done = TRUE;
			break;
		case BTN_NONE:
			break;
		default:
			break;
		}
//		if(mashTemp < 51)
//			mashTemp = 50;
		if(mashTemp >= 80)
			mashTemp = 80;

		initialMashTemp = mashTemp+3;
	}
	return mashTemp;
}
