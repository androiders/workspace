/*
 * mash.c
 *
 *  Created on: 15 sep 2014
 *      Author: packard bell
 */
#include "buttons.h"
#include "mash.h"
#include "lcd.h"

BOOL setupMash(MashProfile * profile)
{
	if(profile == NULL)
		return FALSE;

	setMashType(profile);
	if(profile->type == LinearTemp)
	{
		profile->nrOfBreaks = 1;
		setMashLinearStartTemp(profile);
		setMashLinearStopTemp(profile);
		setMashTimesLoop(profile);
	}
	else if(profile->type == SingleInfusion)
	{
		profile->nrOfBreaks = 1;
		setMashTempsLoop(profile);
		setMashTimesLoop(profile);
		setUseMashOut(profile);
	}
	else if(profile->type == MultiStepInfusion)
	{
		setNumberOfMashBreaks(profile);
		setMashTempsLoop(profile);
		setMashTimesLoop(profile);
		setUseMashOut(profile);
	}
	else
		return FALSE;

	return TRUE;
}

void setMashType(MashProfile * profile)
{
	BOOL done = FALSE;
	MashType type = SingleInfusion;
	while( !done )
	{
		printMashType(0,0,type);
		int8_t mod = getValueFromInput();

		type += mod;

		if(mod == 0)
			done = TRUE;

		if(type > MultiStepInfusion)
			type = LinearTemp;
		if(type < LinearTemp)
			type = MultiStepInfusion;
	}

	profile->type = type;
}

void setUseMashOut(MashProfile * profile)
{
	BOOL done = FALSE;
	uint8_t val = 0;
	int8_t mod = 0;
	while( !done )
	{
		printUseMashOut(val);
		mod = getValueFromInput();

		val+= mod;

		if(mod == 0)
			done = TRUE;

		if(val < 0)
			val = 1;
		if(val > 1)
			val = 0;
	}
	profile->useMashOut = val;

}


void setMashTimesLoop(MashProfile * profile)
{
	for(uint8_t breaks = 0; breaks < profile->nrOfBreaks; breaks++)
	{
		setMashTimeLoop(profile,breaks);
	}
}

void setMashTempsLoop(MashProfile * profile)
{
	for(uint8_t breaks = 0; breaks < profile->nrOfBreaks; breaks++)
	{
		setMashTempLoop(profile,breaks);
	}

}


void setMashLinearStartTemp(MashProfile * profile)
{
	profile->linearStopTemp = getUserValueWithString("Lin. start. tmp",50,20,1);
}

void setMashLinearStopTemp(MashProfile * profile)
{
	profile->linearStopTemp = getUserValueWithString("Lin. stop. tmp",80,60,1);
}


void setNumberOfMashBreaks(MashProfile * profile)
{
	BOOL done = FALSE;
	uint8_t breaks = 2;
	int8_t mod = 0;
	while( !done )
	{
		printStringAndNum("Nr Breaks", breaks);
		mod = getValueFromInput();
		breaks += mod;

		if(mod == 0)
			done = TRUE;

		if(breaks < 2)
			breaks = MAX_NR_OF_BREAKS;
		if(breaks > MAX_NR_OF_BREAKS)
			breaks = 2;
	}
	profile->nrOfBreaks = breaks;
}

void setMashTimeLoop(MashProfile * profile, uint8_t index)
{
	uint8_t done = 0;
	uint8_t mashTime = 10;

	while( !done )
	{
		printStringAndNum("Break Time", mashTime);
		int8_t val = getValueFromInput();

		mashTime += val * 5;

		if(val == 0)
			done = TRUE;

		if(mashTime < 5)
			mashTime = 40;
		if(mashTime > 40)
			mashTime = 5;
	}
	profile->breakTimes[index] = mashTime;
}

void setMashTempLoop(MashProfile * profile, uint8_t index)
{
	uint8_t done = 0;
	uint8_t mashTmp = 20;

	while( !done )
	{
		printStringAndNum("Break Time", mashTmp);
		int8_t val = getValueFromInput();

		mashTmp += val * 2;

		if(val == 0)
			done = TRUE;

		if(mashTmp < 20)
			mashTmp = 80;
		if(mashTmp > 80)
			mashTmp = 20;
	}
	profile->breakTemps[index] = mashTmp;
}

void printMashType(uint8_t x, uint8_t y, MashType type)
{
	lcd_gotoxy(0,0);
	lcd_puts("Mash Profile");
	lcd_gotoxy(0,1);
	switch(type)
	{
	case SingleInfusion:
		lcd_puts("Single Inf.");
		break;
	case MultiStepInfusion:
		lcd_puts("Step Inf.");
		break;
	case LinearTemp:
		lcd_puts("Linear temp");
		break;
	default:
		break;
	}

}

void printUseMashOut(uint8_t yesorno)
{
	lcd_gotoxy(0,0);
	lcd_puts("Mash out?");
	lcd_gotoxy(0,1);
	switch(yesorno)
	{
	case 0:
		lcd_puts("no");
		break;
	case 1:
		lcd_puts("no");
		break;
	default:
		break;
	}
}
