/* Copyright (C) Tor Brodtkorb */

#include "print.h"
#include "usart.h"
#include "gpio.h"
#include "clock.h"
#include "sprint.h"

void print_init(void)
{
	enable_peripheral_clock(14);
	
	gpio_set_function(PIOA, 21, FUNCTION_A);
	gpio_set_function(PIOB, 4, FUNCTION_D);
	
	struct usart_desc print_desc = {
		.baudrate = 115200,
		.data_bits = USART_DATA_8,
		.parity = USART_NONE,
		.stop_bits = USART_STOP_BIT_1
	};
	
	usart_init(USART1, &print_desc);
}

static char print_buffer[256];

void _print(const char* data, ...)
{
	va_list args;
	va_start(args, data);
	u32 size = vsprint(print_buffer, data, args);
	va_end(args);
	
	const char* src = print_buffer;
	while (size--) {
		usart_transmit(USART1, (u8)*src);
		src++;
	}
}


void print(const char* data)
{
	while (*data) {
		usart_transmit(USART1, *(u8 *)data++);
	}
}