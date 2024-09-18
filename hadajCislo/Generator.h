/* 
* Generator.h
*
* Created: 22. 1. 2022 21:31:14
* Author: HP
*/


#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <time.h>

//#include "Board.h"
#include "Led.h"
#include "Display.h"
#include "Eeprom.h"

class Generator
{
//variables
public:
	uint8_t Seed;
	uint8_t Magic;
	uint8_t  nahc, dolh, horh, rozptil, odhad, perc, zpam; // nahodne cislo, dol. hran, hor. h.
	Led rgb;
	Display seg;
protected:
private:

//functions
public:
	Generator();
	~Generator();
	void generuj();
	uint8_t dolHranica();
	uint8_t horHranica();
	void showInteval();
	void presMedziHod();
	uint8_t Rand();
	void Srand(uint8_t val);
	uint8_t odhadCis(uint8_t odhad, uint8_t pokus);
	
protected:
private:
	Generator( const Generator &c );
	Generator& operator=( const Generator &c );
	uint8_t RotateRight(uint8_t val, short nr);

}; //Generator

#endif //__GENERATOR_H__
