/*
* Author: Lukas
*/


#ifndef __LED_H__
#define __LED_H__

#include "Board.h"

class Led
{
	//variables
	public:
	protected:
	private:

	//functions
	public:
	Led();
	~Led();
	void set(bool r,bool g,bool b);
	void set(Colour c);
	void setIntensity(uint8_t r, uint8_t g, uint8_t b);
	void blick(bool r,bool g,bool b, int timeMs);
	void delay_ms(int ms);
	void delay_us(int us);
	void swPwm(Colour c, uint8_t percentage);
	protected:
	private:


}; //Led

#endif //__LED_H__
