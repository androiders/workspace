/*
 * ds12887.h
 *
 *  Created on: 27 nov 2013
 *      Author: androiders
 *
 *      Using motorola timing only. Not memorymapped but driven
 *      from IO port directly
 */

#ifndef DS12887_H_
#define DS12887_H_

#include <inttypes.h>
#include <avr/io.h>

#define DDR(x) (*(&x - 1))      /* address of data direction register of port x */

#define CTRL_PORT 	PORTD
#define DATA_PORT 	PORTC
#define DATA_IN_PORT 	PINC
#define DATA_D0 	7
#define DATA_D1 	6
#define DATA_D2 	5
#define DATA_D3 	4
#define DATA_D4 	3
#define DATA_D5 	2
#define DATA_D6 	1
#define DATA_D7 	0
#define CTRL_AS		2
#define CTRL_RW		1
#define CTRL_DS		0


/**
 * public interface
 */

void ds12887_init();

uint8_t ds12887_read_sec();

uint8_t ds12887_read_minute();

uint8_t ds12887_read_ds_control_a();

uint8_t ds12887_write_ds_control_a(uint8_t data);

uint8_t ds12887_read_ds_control_b();

uint8_t ds12887_write_ds_control_b(uint8_t data);

uint8_t ds12887_read_ds_control_d();

/**
 * low level drivers
 */

#define DS_SECONDS			0x00
#define DS_SECONDS_ALARM	0x01
#define DS_MINUTES			0x02
#define DS_MINUTES_ALARM	0x03
#define DS_HOURS			0x04
#define DS_HOURS_ALARM		0x05
#define DS_DAY				0x06
#define DS_DATE				0x07
#define DS_MONTH			0x08
#define DS_YEAR				0x09
#define DS_CONTROL_A		0x50//0x0a
#define DS_CONTROL_B		0xD0
#define DS_CONTROL_C		0x0c
#define DS_CONTROL_D		0xb0//0x0d

/* DS12C887, DS12C887A only */
#define DS_CENTURY			0x32

#define DS_A_RS0			(1 << 0)
#define DS_A_RS1			(1 << 1)
#define DS_A_RS2			(1 << 2)
#define DS_A_RS3			(1 << 3)
#define DS_A_DV0			(1 << 4)
#define DS_A_DV1			(1 << 5)
#define DS_A_DV2			(1 << 6)
#define DS_A_UIP			(1 << 7)

#define DS_B_DSE			(1 << 0)
#define DS_B_2412			(1 << 1)
#define DS_B_DM				(1 << 2)
#define DS_B_SQWE			(1 << 3)
#define DS_B_UIE			(1 << 4)
#define DS_B_AIE			(1 << 5)
#define DS_B_PIE			(1 << 6)
#define DS_B_SET			(1 << 7)

#define DS_C_UF				(1 << 4)
#define DS_C_AF				(1 << 5)
#define DS_C_PF				(1 << 6)
#define DS_C_IRQF			(1 << 7)

#define DS_D_VRT			(1 << 7)


uint8_t ds12887_read_address(uint8_t addr);

uint8_t ds12887_write_address(uint8_t data, uint8_t addr);


#endif /* DS12887_H_ */
