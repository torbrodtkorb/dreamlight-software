/* Copyright (C) Tor Brodtkorb */

#include "print.h"
#include "usart.h"
#include "gpio.h"

void print_init(void)
{
	enable_peripheral_clock(14);
	
	struct usart_desc print_desc = {
		.baudrate = 115200,
		.data_bits = USART_DATA_8,
		.parity = USART_NONE,
		.stop_bits = USART_STOP_BIT_1
	};
	
	usart_init(USART1, &print_desc);
	
	gpio_set_function(PIOA, 21, FUNCTION_A);
	gpio_set_function(PIOB, 4, FUNCTION_D);
}

void print(const char* data)
{
	while (*data){
		usart_transmit(USART1, *data);
		data++;
	}
}

void printl(const char* data)
{
	while (*data){
		usart_transmit(USART1, *data);
		data++;
	}
	usart_transmit(USART1, '\n');
}
