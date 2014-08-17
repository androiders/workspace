/*
 * ds12887.c
 *
 *  Created on: 27 nov 2013
 *      Author: androiders
 */


#include <util/delay.h>
#include "ds12887.h"
#include "lcd.h"

static inline void _delayFourCycles(unsigned int __count)
{
    if ( __count == 0 )
        __asm__ __volatile__( "rjmp 1f\n 1:" );    // 2 cycles
    else
        __asm__ __volatile__ (
    	    "1: sbiw %0,1" "\n\t"
    	    "brne 1b"                              // 4 cycles/loop
    	    : "=w" (__count)
    	    : "0" (__count)
    	   );
}

void ds12887_init()
{
	uint8_t data = 0x00;
	//set ctrl port to outpu
	DDR(CTRL_PORT)  |= _BV(CTRL_AS);
    DDR(CTRL_PORT)  |= _BV(CTRL_DS);
    DDR(CTRL_PORT)  |= _BV(CTRL_RW);
//	DDRE = 0xFF;
//    PORTE &= ~(_BV(CTRL_AS));
//	PORTC &= ~(_BV(CTRL_DS));
//	PORTC &= ~(_BV(CTRL_RW));

    //start oscillator and set in BCM mode
    do{
    	data = ds12887_read_ds_control_a();
    }while(data & DS_A_UIP);

    data = ds12887_read_ds_control_d();
    if(data & DS_D_VRT)
    	lcd_puts("vrt OK");
    else
    	lcd_puts("vrt bad");

    data &= ~(DS_A_DV0 | DS_A_DV1 | DS_A_DV2);
    data |= DS_A_DV1;
    data = 0xF4;
    ds12887_write_ds_control_a(data);

    data = ds12887_read_ds_control_a();
    lcd_gotoxy(0,1);
    lcd_puts("ca:");
    lcd_put_num(data);

    data = 0x00;
    //data = ds12887_read_ds_control_b();
   	/* Switch to binary mode from BCD */
   	data &= ~(DS_B_DM);
   	data |= DS_B_SQWE;
   	ds12887_write_ds_control_b(data);
}

uint8_t ds12887_read_sec()
{
	//set address on data port pins
	return ds12887_read_address(DS_SECONDS);


}
//
//void ds12887_read_minute();

uint8_t ds12887_read_ds_control_a()
{
	return ds12887_read_address(DS_CONTROL_A);
}

uint8_t ds12887_write_ds_control_a(uint8_t data)
{
	return ds12887_write_address(data,DS_CONTROL_A);
}

uint8_t ds12887_read_ds_control_b()
{
	return ds12887_read_address(DS_CONTROL_B);
}

uint8_t ds12887_write_ds_control_b(uint8_t data)
{
	return ds12887_write_address(data,DS_CONTROL_B);
}

uint8_t ds12887_read_ds_control_d()
{
	return ds12887_read_address(DS_CONTROL_D);
}

uint8_t util_create_addr(uint8_t addr)
{
//	uint8_t new_addr = 0x00;
//	new_addr |= (addr & 0x01) << DATA_D0;
//	new_addr |= (addr & 0x02) << DATA_D1;
//	new_addr |= (addr & 0x04) << DATA_D2;
//	new_addr |= (addr & 0x08) << DATA_D3;
//	new_addr |= (addr & 0x10) << DATA_D4;
//	new_addr |= (addr & 0x20) << DATA_D5;
//	new_addr |= (addr & 0x40) << DATA_D6;
//	new_addr |= (addr & 0x80) << DATA_D7;

	return addr;
}

uint8_t ds12887_read_address(uint8_t addr)
{
	uint8_t sec = 0x0a;
	DDRC = 0xFF;
	 // rtc_tris=0b11100000;//set the tris of C for setting address
	  //rtc_tris.ad=0x00; //set the tris of D for setting address
	  //rtc     =0b00011110;//set C for for setting address
	PORTB |= _BV(CTRL_AS);
	PORTB |= _BV(CTRL_RW);
	PORTB |= _BV(CTRL_DS);
//	  rtc.ad=addr;      //put address on bus
	PORTC = addr;
	_delayFourCycles(1);
//	  #asm nop #endasm    //pause
//	rtc.as=0;           //latch
	PORTB &= ~(_BV(CTRL_AS));
	_delayFourCycles(1); // pause
//	  rtc_tris.ad=0xFF; //set the tris of D for reading data
	PORTC = 0x00;
	DDRC = 0x00;

//	  rtc.ds=0;           //release
	  PORTB &= ~(_BV(CTRL_DS));
//	  #asm nop #endasm    //pause
	  _delayFourCycles(1);
//	  data=rtc.ad;      //read the data from the bus
	  sec = PINC;
//	  rtc_tris_r(); //set the tris of B  and D to ALL INPUTS
//	  return(data);

	//set dataport to output to write adress
	//DDR(DATA_PORT) = 0xFF;
//	DDRC = 0xFF;

//	_delay_us(1);
	//put address on data port
//	DATA_PORT = util_create_addr(addr);

//	_delay_us(1);
	//strobe AS

//	_delay_us(1);
	//set data port to read input
//	_delay_us(1);
	//set WR to read op
//	PORTE |= _BV(CTRL_RW);
//	_delay_us(1);
	//set DS high
//	PORTE |= _BV(CTRL_DS);
	//_delay_us(1);
//
//	sec = PINC;
//	//now we have the data on the data bus!
////	sec |= (DATA_IN_PORT & ( 0x01 << DATA_D0));// >> DATA_D0;
////	sec |= (DATA_IN_PORT & ( 0x01 << DATA_D1));// >> DATA_D1;
////	sec |= (DATA_IN_PORT & ( 0x01 << DATA_D2));// >> DATA_D2;
////	sec |= (DATA_IN_PORT & ( 0x01 << DATA_D3));// >> DATA_D3;
////	sec |= (DATA_IN_PORT & ( 0x01 << DATA_D4));// >> DATA_D4;
////	sec |= (DATA_IN_PORT & ( 0x01 << DATA_D5));// >> DATA_D5;
////	sec |= (DATA_IN_PORT & ( 0x01 << DATA_D6));// >> DATA_D6;
////	sec |= (DATA_IN_PORT & ( 0x01 << DATA_D7));// >> DATA_D7;
//
//	_delay_us(1);

//	PORTE &= ~(_BV(CTRL_RW));

	return sec;
}


uint8_t ds12887_write_address(uint8_t data, uint8_t addr)
{
	//set dataport to output to write adress
	DDRC = 0xFF;
	//_delay_us(1);

//	rtc_tris_w();
//	  rtc.cs_bar=0;//chip active
//	  rtc.ad=addr; //addr is on bus
	  PORTC = addr;//util_create_addr(addr);
//	  rtc.rw_bar=0;//write mode
	  PORTB &= ~(_BV(CTRL_RW));

//	  rtc.ds=0;    //data strob idle
	  PORTB &= ~(_BV(CTRL_DS));

//	  rtc.as=1;    //addr strob
	  PORTB |= _BV(CTRL_AS);

	  _delayFourCycles(1); // pause

//	  rtc.as=0;    //latch address
	  PORTB &= ~(_BV(CTRL_AS));

//	  rtc.ds=1;    //data strob idle
	  PORTB |= _BV(CTRL_DS);

//	  rtc.ad=data; //data is on bus
	  PORTC = data;
	  _delayFourCycles(1);
//	  rtc.ds=0;    //latch data
	  PORTB &= ~(_BV(CTRL_DS));

//	  rtc_tris_r(); //set the tris of C  and D to ALL INPUTS
	  DDRC = 0x00;

	//put address on data port

	//_delay_us(1);


	//strobe AS
	//_delay_us(1);

	//set WR to write op
	//_delay_us(1);

	//set DS high
	//_delay_us(1);

	//put data on data port
	//util_create_addr(data); //bad function name!! (it converts any 8 bit data)
//	_delay_us(1);
//	CTRL_PORT |= _BV(CTRL_DS);
//	_delay_us(1);



	//_delay_us(1);


	return 0;
}
