/*
  OzOLED.h - 0.96' I2C 128x64 OLED Driver Library
  2014 Copyright (c) OscarLiang.net  All right reserved.
 
  Author: Oscar Liang
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

*/

#ifndef TinyOzOLED_data_H
#define TinyOzOLED_data_H

#include <Arduino.h>

#define TinyOzOLED_Max_X					128	//128 Pixels
#define TinyOzOLED_Max_Y					64	//64  Pixels

#define OLED_ADDRESS					0x3C
#define I2C_400KHZ						1	// 0 to use default 100Khz, 1 for 400Khz

// registers
#define TinyOzOLED_COMMAND_MODE				0x00
#define TinyOzOLED_DATA_MODE				0x40

// commands
#define TinyOzOLED_CMD_DISPLAY_OFF			0xAE
#define TinyOzOLED_CMD_DISPLAY_ON			0xAF

#define TinyOzOLED_CMD_NORMAL_DISPLAY		0xA6
#define TinyOzOLED_CMD_INVERSE_DISPLAY		0xA7

#define TinyOzOLED_CMD_SET_BRIGHTNESS		0x81

#define TinyOzOLED_RIGHT_SCROLL				0x26
#define TinyOzOLED_LEFT_SCROLL				0x27
#define TinyOzOLED_SET_VERTICAL_SCROLL_AREA 0xA3
#define TinyOzOLED_VERTICAL_RIGHT_SCROLL	0x29
#define TinyOzOLED_VERTICAL_LEFT_SCROLL		0x2A
#define TinyOzOLED_CMD_ACTIVATE_SCROLL		0x2F
#define TinyOzOLED_CMD_DEACTIVATE_SCROLL	0x2E

//#define HORIZONTAL_ADDRESSING	0x20
//#define PAGE_ADDRESSING			0x22

#define MEMORY_ADDRESS_CMD			0x20
#define PAGE_ADDRESSING_MODE		0x02
#define HORIZONTAL_ADDRESSING_MODE	0x00
#define VERTICAL_ADDRESSING_MODE	0x01

#define SET_COLUMN_ADDRESS_CMD		0x21
#define SET_PAGE_ADDRESS_CMD		0x22

#define Scroll_Left				0x00
#define Scroll_Right			0x01
#define Scroll_Up				0x02
#define Scroll_Down				0x03

#define Scroll_2Frames			0x07
#define Scroll_3Frames			0x04
#define Scroll_4Frames			0x05
#define Scroll_5Frames			0x00
#define Scroll_25Frames			0x06
#define Scroll_64Frames			0x01
#define Scroll_128Frames		0x02
#define Scroll_256Frames		0x03


class TinyOzOLED {

public:

	byte addressingMode;

	void sendCommand(byte command);
	void sendCommands(byte * commands, byte nrOfCommands);
	void sendData(byte Data);

	void printChar(char c, byte X=255, byte Y=255);
	void printString(const char *String, byte X=255, byte Y=255, byte numChar=255);
	byte printNumber(long n, byte X=255, byte Y=255);
	byte printNumber(float float_num, byte prec=6, byte Y=255, byte numChar=255);
	void printBigNumber(const char *number, byte column=0, byte page=0, byte numChar=255); 
	void drawBitmap(const byte *bitmaparray, byte X, byte Y, byte width, byte height);

	void init();
	
	void setCursorXY(byte Column, byte Row);
	void clearDisplay();
	//void clearPage(byte page);
	
	void setNormalDisplay();
	void setInverseDisplay();

	void setPowerOff();
	void setPowerOn();

	void setAllOn(byte onOff);

	void setPageAddressingMode();
	void setHorizontalAddressingMode();
	void setVerticalAddressingMode();

	void setBrightness(byte Brightness);
	
	void scrollRight(byte start, byte end, byte speed);
	void scrollLeft(byte start, byte end, byte speed);
	void scrollDiagRight();
	void scrollDiagLeft();
	void setActivateScroll(byte direction, byte startPage, byte endPage, byte scrollSpeed);
	void setDeactivateScroll();

private:

	void setAddressingMode(byte mode);

};

extern TinyOzOLED TinyOzOled;  // TinyOzOLED object 

#endif


