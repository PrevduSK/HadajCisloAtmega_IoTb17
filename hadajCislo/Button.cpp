/* 
* Author: Lukas
*/


#include "Button.h"

Button* Button::button_ptr;

// default constructor
Button::Button()
{
	cbi(DDRD,BTN);		// set as input
	sbi(PORTD,BTN);		// set pull-up
	button_ptr = this; 
	is_pressed = false;
	counter = 0;
} //Button

// default destructor
Button::~Button()
{
	EIMSK &=~(1<<INT0);		// turn off interrupt
} //~Button

bool Button::isPressed(void)
{
/*	while((PIND & (1<<BTN))!=0){};			// wait, BTN=1
	_delay_ms(10);							// delay
	while((PIND & (1<<BTN))==0){};			// wait for release button	 
	return true;							// if BTN = 0  . . . pressed
*/
	if((PIND & (1<<BTN))==0) return true;	// pressed
	else return false;						// released
}

void Button::initInterrupt(externInt edge)
{
	EICRA |= edge;			// bits ISC00, ISC01
	sbi(EIMSK,INT0);		// enable extern interrupt 0
}

void Button::interruptHandler(void)
{
	tbi(PORTD,G_LED);
	is_pressed = true;
	counter++;
	if(counter>15)
		counter=0;
}

uint8_t Button::getCounter(void)
{
	return counter;
}

bool Button::getPressed(void)
{
	return is_pressed;
}

void Button::setPressed(bool pressed)
{
	is_pressed = pressed;
}

ISR(INT0_vect)
{
	Button::button_ptr->interruptHandler();
}