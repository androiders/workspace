/*
 * buttons.c
 *
 *  Created on: 15 sep 2014
 *      Author: packard bell
 */

#include "buttons.h"
#include "utils.h"
#include <util/delay.h>

uint8_t readButtons()
{
	static BOOL okForNewPress = TRUE;
	volatile uint8_t input = PIND;
	uint8_t ret = BTN_NONE;
	_delay_ms(20);

	//dont allow holding of buttons
	if(okForNewPress == FALSE)
		return BTN_NONE;

	if(input & _BV(UP))
		ret = BTN_UP;
	else if(input & _BV(DOWN))
		ret = BTN_DOWN;
	else if(input & _BV(OK))
		ret = BTN_OK;
	else
		ret = BTN_NONE;

	if(input != 0)
		okForNewPress = FALSE;
	if(ret == BTN_NONE)
		okForNewPress = TRUE;

	return ret;
}

void waitForOk()
{
	while(readButtons() != BTN_OK);
}
