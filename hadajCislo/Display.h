/* 
* Author: Lukas
*/


#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "Board.h"

class Display
{
//variables
public:
protected:
private:

//functions
public:
	Display();
	~Display();
	void show(uint8_t character);
	void circle();
	void showMultip(uint8_t character, unsigned int total_cas, uint8_t zobraz);
protected:
private:
	void display(uint8_t character);
	void myDelay(uint8_t ms, unsigned int cas);


}; //Display

#endif //__DISPLAY_H__
