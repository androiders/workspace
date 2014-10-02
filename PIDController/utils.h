/*
 * utils.h
 *
 *  Created on: 15 sep 2014
 *      Author: packard bell
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdlib.h>
#include <avr/io.h>

#define BOOL uint8_t
#define TRUE 1
#define FALSE 0

uint8_t getUserValueWithString(const char * str, uint8_t max, uint8_t min, uint8_t delta);

/**
 * returns 0 if OK_BTN is pressed, 1 if BTN_UP is presseed and -1 if BTN_DOWN is pressed
 * a value of -99 is returned if no button was pressed
 */
int8_t getValueFromInput();

void printStringAndNum(const char * string, uint8_t tmp);

#endif /* UTILS_H_ */
