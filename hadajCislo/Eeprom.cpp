/* 
* Eeprom.cpp
*
* Created: 18. 11. 2021 9:24:59
* Author: HP
*/


#include "Eeprom.h"

// default constructor
Eeprom::Eeprom()
{
} //Eeprom

// default destructor
Eeprom::~Eeprom()
{
} //~Eeprom

void Eeprom::write (uint16_t addr, uint8_t data)
{
	while(EECR & (1<<EEPE));
	
	EEAR = addr;
	EEDR = data;
	
	EECR |= (1<<EEMPE);
	
	EECR |= (1<<EEPE);
}

char Eeprom::read(uint16_t addr)
{
	while(EECR & (1<<EEPE));
	
	EEAR = addr;
	EECR |= (1<<EERE);
	
	return EEDR;
}