/* Copyright (C) Tor Brodtkorb */

#include "usart.h"

void usart_init(Usart* usart, struct usart_desc* desc)
{
	/* Disable and reset transmitter and receiver */
	usart->US_CR = (1 << 5) | (1 << 7) | (1 << 2) | (1 << 3);
	
	/*
	* Write the mode register
	* Disable Receiver Timeout Register and Transmitter Timeguard Register
	*/
	usart->US_RTOR = 0;
	usart->US_TTGR = 0;
	usart->US_MR = (desc->parity << 9) | (desc->stop_bits << 12) | (desc->data_bits << 6) | (1 << 20);
	
	/* Write the baud register */
	usart->US_BRGR = (150000000/(16*desc->baudrate));
	
	/* Enable transmitter and receiver */
	usart->US_CR = (1 << 4) | (1 << 6);
	
	/* Enable receive interrupt */
	usart->US_IER = (1 << 0);
	
}
