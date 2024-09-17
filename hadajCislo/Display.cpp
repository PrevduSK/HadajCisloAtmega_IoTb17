/* 
* Author: Lukas
*/


#include "Display.h"

// default constructor
Display::Display()
{
	/* Set as outputs */
	sbi(DDRC,SER);
	sbi(DDRC,OE);
	#if BOARD_TYPE == 2018
		sbi(DDRD,RCLK);
	#else 
		sbi(DDRB,RCLK);
	#endif
	sbi(DDRB,SRCLK);
	show(18);
} //Display

// default destructor
Display::~Display()
{
} //~Display

void Display::show(uint8_t character)
{
	uint8_t result;
	character= character & 0x1f;
	switch(character)
	{
		case 0: result=zero; break;
		case 1: result=one; break;
		case 2: result=two; break;
		case 3: result=three; break;
		case 4: result=four; break;
		case 5: result=five; break;
		case 6: result=six; break;
		case 7: result=seven; break;
		case 8: result=eight; break;
		case 9: result=nine; break;
		case 10: result=ahex; break;
		case 11: result=bhex; break;
		case 12: result=chex; break;
		case 13: result=dhex; break;
		case 14: result=ehex; break;
		case 15: result=fhex; break;
		case 16: result=dot; break;
		case 17: result=err; break;
		case 18: result=non; break;
		default: result=non;
	}	
	this->display(result);			// display(result)
}

/* private method */
void Display::display(uint8_t character)
{
	sbi(PORTC,OE);				// set output to HI (high impedance)
	for(uint8_t i=0;i<8;i++)
	{
		if((character & 0b10000000)==0b10000000) sbi(PORTC,SER);else cbi(PORTC,SER);	//data
		sbi(PORTB,SRCLK);
		cbi(PORTB,SRCLK);	// clock
		character=character<<1;
	}
	#if BOARD_TYPE == 2018
		sbi(PORTD,RCLK);		//	transcript from shift register to memory
		cbi(PORTD,RCLK);		//  impulse
	#else
		sbi(PORTB,RCLK);		//	transcript from shift register to memory
		cbi(PORTB,RCLK);		//  impulse
	#endif
	cbi(PORTC,OE);			//	set output
}

void Display::circle()
{
	uint8_t pom =0b00000001;
	for (uint8_t i=0 ; i<6; i++)
	{
		display(pom);
		_delay_ms(80);
		pom = pom<<1;
	}
}

void Display::showMultip(uint8_t character, unsigned int total_cas, uint8_t zobraz)
{
	uint8_t pomC, pomZ;
	unsigned int poCas1, poCas2, scCas = 0;
	if( character > 9 )
	{ 
		pomC = character/ 10;
		pomZ = character% 10;
		poCas1 = total_cas/2 / zobraz / 10 /2; // prestavka
		poCas2 = total_cas/2 / zobraz - poCas1;
		while(scCas < total_cas){
			show(18);
			show(pomC);
			myDelay(1,poCas2);
			show(18);
			myDelay(1,poCas1);
			show(pomZ);
			myDelay(1,poCas2);
			show(18);
			myDelay(1,poCas1);
			scCas += 2*poCas2 + 2*poCas1;
			printf("scCas: %d \r\n", scCas);
		}
		
	} else {	
		show(character);
		myDelay(1,total_cas/2);
	}
}

void Display::myDelay(uint8_t ms, unsigned int cas)
{
	if( ms == 1 ){ // ms
		for (unsigned int i = 0; i< cas; ++i)
			_delay_ms(1);
		
	} else { // us
		for (unsigned int i = 0; i< cas; ++i)
		_delay_us(1);
	}
}