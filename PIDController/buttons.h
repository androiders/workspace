/*
 * buttons.h
 *
 *  Created on: 15 sep 2014
 *      Author: packard bell
 */

#include "utils.h"

#ifndef BUTTONS_H_
#define BUTTONS_H_

//inputs
#define OK PD0
#define UP PD2
#define DOWN PD4

//buttons
#define BTN_NONE 0
#define BTN_OK 	 1
#define BTN_UP 	 2
#define BTN_DOWN 3

uint8_t readButtons();

void waitForOk();

#endif /* BUTTONS_H_ */
