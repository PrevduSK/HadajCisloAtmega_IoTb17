/* 
* Author: Lukas
*/


#ifndef __UART_H__
#define __UART_H__

#include "Board.h"


class Uart
{
//variables
public:
protected:
private:
	FILE *uart_ptr;
//functions
public:
	Uart();
	~Uart();
	// HW implementation
	static int hwSendByte(char data, FILE *stream);
	static int hwReceiveByte(FILE *stream);
	//char hwReceiveChar();
	
	// SW implementation
	static int swSendByte(char data, FILE *stream);
	static int swReceiveByte(FILE *stream);
	
protected:
private:


}; //Uart

#endif //__UART_H__
