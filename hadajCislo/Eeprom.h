/* 
* Eeprom.h
*
* Created: 18. 11. 2021 9:24:59
* Author: HP
*/

#include "Board.h"

#ifndef __EEPROM_H__
#define __EEPROM_H__


class Eeprom
{
//variables
public:
protected:
private:

//functions
public:
	Eeprom();
	~Eeprom();
	static void write(uint16_t addr, uint8_t data);
	static char read(uint16_t addr);
protected:
private:
	Eeprom( const Eeprom &c );
	Eeprom& operator=( const Eeprom &c );

}; //Eeprom

#endif //__EEPROM_H__
