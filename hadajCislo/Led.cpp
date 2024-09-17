/*
* Author: Lukas
*/


#include "Led.h"

// default constructor
Led::Led()
{
	/* set as outputs */
	sbi(DDRD,R_LED);
	sbi(DDRD,G_LED);
	#if BOARD_TYPE == 2018
		sbi(DDRD,B_LED);
	#else
		sbi(DDRB,B_LED);
	#endif
	
	set(false,false,false);	// set all leds off
	
	// Fast PWM
	// CLKIO/256
	sbi(TCCR0A,WGM00);		// set fast PWM for TC0
	sbi(TCCR0A,WGM01);		// set fast PWM for TC0
	sbi(TCCR0B,CS02);		// clkio/256 (183 Hz) for TC0
	
	sbi(TCCR2A,WGM20);		// set fast PWM for TC2
	sbi(TCCR2A,WGM21);		// set fast PWM for TC2
	sbi(TCCR2B,CS22);		// clkio/256 (183 Hz) for TC2
	
	#if BOARD_TYPE == 2017
		sbi(TCCR1A,WGM10);	// set fast PWM (8-bit) for TC1
		sbi(TCCR1A,WGM12);	// set fast PWM (8-bit) for TC1
		sbi(TCCR1B,CS12);	// clkio/256 (183 Hz) for TC1
	#endif
	
} //Led

// default destructor
Led::~Led()
{
	
} //~Led

void Led::set(bool r,bool g,bool b)
{
	#if BOARD_TYPE == 2018
		if(r) cbi(PORTD,R_LED); else sbi(PORTD,R_LED);
		if(g) cbi(PORTD,G_LED); else sbi(PORTD,G_LED);
		if(b) cbi(PORTD,B_LED); else sbi(PORTD,B_LED);		
	#else
		if(r) sbi(PORTD,R_LED); else cbi(PORTD,R_LED);
		if(g) sbi(PORTD,G_LED); else cbi(PORTD,G_LED);
		if(b) sbi(PORTB,B_LED); else cbi(PORTB,B_LED);
	#endif
}

void Led::setIntensity(uint8_t r, uint8_t g, uint8_t b)
{
	#if BOARD_TYPE == 2018		/* 2018 Board */
		if(r==0)
		{
			cbi(TCCR0A,COM0A0);
			cbi(TCCR0A,COM0A1);
			sbi(PORTD,R_LED);
		}
		else
		{
			sbi(TCCR0A, COM0A0);
			sbi(TCCR0A, COM0A1);
			OCR0A = r;
		}

		if(g==0)
		{
			cbi(TCCR2A,COM2B0);
			cbi(TCCR2A,COM2B1);
			sbi(PORTD,G_LED);
		}
		else
		{
			sbi(TCCR2A, COM2B0);
			sbi(TCCR2A, COM2B1);
			OCR2B = g;
		}

		if(b==0)
		{
			cbi(TCCR0A,COM0B0);
			cbi(TCCR0A,COM0B1);
			sbi(PORTD,B_LED);
		}
		else
		{
			sbi(TCCR0A, COM0B0);
			sbi(TCCR0A, COM0B1);
			OCR0B = b;
		}
	#else			/* 2017 Board */
		if(r==0)
		{
			cbi(TCCR0A,COM0A0);
			cbi(TCCR0A,COM0A1);
			cbi(PORTD,R_LED);
		}
		else
		{
			cbi(TCCR0A, COM0A0);
			sbi(TCCR0A, COM0A1);
			OCR0A = r;
		}

		if(g==0)
		{
			cbi(TCCR2A,COM2B0);
			cbi(TCCR2A,COM2B1);
			cbi(PORTD,G_LED);
		}
		else
		{
			cbi(TCCR2A, COM2B0);
			sbi(TCCR2A, COM2B1);
			OCR2B = g;
		}

		if(b==0)
		{
			cbi(TCCR1A,COM1A0);
			cbi(TCCR1A,COM1A1);
			cbi(PORTB,B_LED);
		}
		else
		{
			cbi(TCCR1A, COM1A0);
			sbi(TCCR1A, COM1A1);
			OCR1A = b;
		}		
	#endif
	
}

void Led::set(Colour c)
{
	switch(c)
	{
		case 0:		set(1,0,0); // red
					break;
		case 1:		set(0,1,0); // green
					break;
		case 2:		set(0,0,1);	//blue
					break;
		case 3:		set(1,0,1); //magenta
					break;
		case 4:		set(0,1,1);	//cyan
					break;
		case 5:		set(1,1,0); //yellow
					break;
		case 6:		set(1,1,1); //white // light, ON
					break;
		default:	set(0,0,0);	//dark, OFF
	}
}

void Led::blick(bool r,bool g,bool b, int timeMs)
{
	this->set(r,g,b);
	for(int i=0; i<timeMs; i++) _delay_ms(1);
	this->set(0,0,0);
	for(int i=0; i<timeMs; i++) _delay_ms(1);
}

void Led::delay_ms(int ms)
{
	for(int i=0; i<ms; i++) _delay_ms(1);
}

void Led::delay_us(int us)
{
	for(int i=0; i<us; i++) _delay_us(1);
}

void Led::swPwm(Colour c, uint8_t percentage)
{
	if(percentage == 0)
	{
		set(0,0,0);
		return;
	}
	if(percentage>=100)
	{
		set(c);
		return;
	}
	set(c);
	delay_us(percentage);
	set(0,0,0);
	delay_us(100-percentage);
}