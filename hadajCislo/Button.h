/*
* Author: Lukas
*/


#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Board.h"

class Button
{
	//variables
	public:
		static Button* button_ptr;
	protected:
	private:
	// volatile koli konzistencii dat, aby sa kladli na jednomiseto, bud register alebo pamet
		volatile bool is_pressed;
		volatile uint8_t counter;
	//functions
	public:
	Button();
	~Button();
	bool isPressed(void);
	void interruptHandler(void);
	void initInterrupt(externInt edge);
	uint8_t getCounter();
	bool getPressed(void);
	void setPressed(bool pressed);
	protected:
	private:


}; //Button

#endif //__BUTTON_H__
