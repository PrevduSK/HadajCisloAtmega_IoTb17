/* 
* Author: Lukas
*/


#include "Uart.h"

// default constructor
Uart::Uart()
{
	sbi(DDRD,E_OFF);
	//cbi(DDRD,E_OFF);
	DDRD |= (1<<HTX);					// Tx as output (not necessary, when TXEN is set, also TX is set as output)
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);	// BAUDERATE
	UBRR0L = (uint8_t)UBRR_VALUE;
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);  // 8 bits, no parity, 1 stop
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);	// enable rx and tx

	UCSR0A |= (1<<U2X0);				// double speed mode
	
	/* SW UART */
	cbi(DDRC,SRX);			// Set as input
	sbi(DDRC,STX);			// set as output
	sbi(PORTC,STX);			// log.1 on STX
	sbi(PORTC,SRX);			// pull-up
	
	uart_ptr = fdevopen(hwSendByte, hwReceiveByte);		//send , receive methods - HW UART
//	uart_ptr = fdevopen(swSendByte, swReceiveByte);		//send , receive methods - SW UART;
	stdout = stdin = uart_ptr;
	
	sbi(UCSR0B, RXCIE0);    // RX conplere interapt preusenie pri praiati znaku
	sbi(UCSR0A, RXC0);
} //Uart

// default destructor
Uart::~Uart()
{
} //~Uart

/************************************************************ HW UART ************************************************************/
int Uart::hwSendByte(char data, FILE *stream)
{
	while(!(UCSR0A & (1<<UDRE0))){};
	UDR0 = data;
	return 0;
}

int Uart::hwReceiveByte(FILE *stream)
{
	sbi(DDRD,E_OFF);
	//cbi(DDRD,E_OFF);
	uint8_t data;
	while(!(UCSR0A & (1<<RXC0))){};
	data = UDR0;
	//USART_send_byte(u8data,stream);  //echo
	return data;
}
/*
char Uart::hwReceiveChar()
{
	sbi(DDRD,E_OFF);
	cbi(DDRD,E_OFF);
	//char data;
	while(!(UCSR0A & (1<<RXC0))){};
	//data = UDR0;
	//USART_send_byte(u8data,stream);  //echo
	return UDR0;
} */
/*********************************************************************************************************************************/

/************************************************************ SW UART ************************************************************/
/* Baud rate : 9600  */
/* Data		 : 8 bit */
/* Parity	 : none  */
/* Stop bits : 1 bit */
int Uart::swSendByte(char data, FILE *stream)
{
	cbi(PORTC,STX);						// start bit
	_delay_us(104);						// wait 104 us
	for(uint8_t i = 0; i < 8; i++)
	{
		if((data & 1) == 1)sbi(PORTC,STX); else cbi(PORTC,STX);		// LSB first
		_delay_us(104);					// duration of bit
		data = data >> 1;
	}
	sbi(PORTC,STX);						// 1 stop bit
	_delay_us(104);						// 104 us
	return 0;
}

int Uart::swReceiveByte(FILE *stream)
{
	uint8_t data = 0;
	while((PINC & (1<<SRX))!= 0){}		// wait until SRX = log.0
	_delay_us(52);						// wait 104/2 = 52 us (half bit duration)	
	_delay_us(104);						// wait until half of the first data bit
	for(uint8_t i = 0; i < 8; i++)		// read 8 data bits (LSB-->MSB)
	{	
		data = data>>1;	
		if((PINC & (1<<SRX)) == (1<<SRX)) data = data | 0b10000000;
		_delay_us(104);					// 104 us	
	}
	return data;
}
/*********************************************************************************************************************************/
	/* bude vraciat znak stlaceni na klavesnici, 
	* toto nieje korektne treba to zapuzdrit */
ISR(USART_RX_vect)
{
	printf("%c", UDR0);
}