/*
 *  Author: Lukas
 */ 


#ifndef BOARD_H_
#define BOARD_H_

#define BOARD_TYPE 2017	 // 2018

#ifndef F_CPU
	#define F_CPU 12000000UL
#endif


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
/************************** MACROS ****************************/
#define sbi(x,y) x |= _BV(y)		// set bit (1<<y) [log. 1]
#define cbi(x,y) x &= ~(_BV(y))		// clear bit - using bitwise AND operator [log. 0]
#define tbi(x,y) x ^= _BV(y)		// toggle bit - using bitwise XOR operator
/**************************************************************/

/************************** RGB ****************************/
#define R_LED PORTD6
#define G_LED PORTD3
#if BOARD_TYPE == 2018
	#define B_LED PORTD5
#else
	#define B_LED PORTB1
#endif

 enum Colour {						// enumerable type - default: 0, 1, 2, 3...
	 red, green, blue, magenta, cyan, yellow, on, off
 };
/***********************************************************/

/************************** BUTTON ****************************/
#define BTN PORTD2
/**************************************************************/

/************************** DISPLAY ****************************/
#define SER PORTC5
#define OE PORTC4
#if BOARD_TYPE == 2018
	#define RCLK PORTD7
#else
	#define RCLK PORTB2
#endif
#define SRCLK PORTB1

/* numbers definitions */
//              MSB           LSB
//              H G F E D C B A
#define zero	0b00111111
#define one		0b00000110
#define two		0b01011011
#define three	0b01001111
#define four	0b01100110
#define five	0b01101101
#define six		0b01111101
#define seven	0b00000111
#define eight	0b01111111
#define nine	0b01101111
#define ahex	0b01110111
#define bhex	0b01111100
#define chex	0b01011000
#define dhex	0b01011110
#define ehex	0b01111001
#define fhex	0b01110001
#define dot		0b10000000
#define err		0b01001001
#define non		0b00000000
/***************************************************************/

/************************** UART ****************************/
#define HTX PORTD1
#define HRX PORTD0

#define STX PORTC2
#define SRX PORTC3

#define E_OFF PORTD5

#define BAUDERATE 115200   // 115200
#define UBRR_VALUE ((F_CPU / (BAUDERATE * 8L)) -1)  //   8....51  ,  16.....25  12.....12
/***************************************************************/

/************************* I2C, TWI ****************************/
#define SDA PORTB0
#define SCL PORTD7
/**************************************************************/
enum externInt{		// EICRA
	low,			// 00
	change,			// 01
	fall,			// 10
	rising			// 11
};

#endif /* BOARD_H_ */