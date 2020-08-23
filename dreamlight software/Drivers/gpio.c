/* Copyright (C) Tor Brodtkorb */

#include "gpio.h"

void gpio_set_function(Pio* port, u8 pin, enum gpio_function func)
{
	
	if (port == PIOB) {
		if ((pin == 4) || (pin == 5) || (pin == 6) || (pin == 7) || (pin == 12)) {
			MATRIX->CCFG_SYSIO |= (1 << pin);
		}
	}
	
	if (func == FUNCTION_GPIO) {
		/* Enable GPIO */
		port->PIO_PER = (1 << pin);
	} else {
		/* Disable GPIO which enables the peripheral control over the pin. */  
		port->PIO_PDR = (1 << pin);
		
		if (func & 0b01) {
			port->PIO_ABCDSR[0] |= (1 << pin);
		} else {
			port->PIO_ABCDSR[0] &= ~(1 << pin);	
		} if (func & 0b10) {
			/* This if/else statement is in both if and else statement over. */ 
			port->PIO_ABCDSR[1] |= (1 << pin);
		} else {
			port->PIO_ABCDSR[1] &= ~(1 << pin);
		}
	}
}


void gpio_set_direction(Pio* port, u8 pin, enum gpio_dir dir)
{
	if (dir == GPIO_OUTPUT) {
		port->PIO_OER = (1 << pin);
	} else {
		port->PIO_ODR = (1 << pin);
	}
}

void gpio_set(Pio* port, u8 pin)
{
	port->PIO_SODR = (1 << pin);
}

void gpio_clear(Pio* port, u8 pin)
{
	port->PIO_CODR = (1 << pin);
}

void gpio_toggle(Pio* port, u8 pin)
{
	if (port->PIO_ODSR & (1 << pin)) {
		port->PIO_CODR = (1 << pin);
	} else {
		port->PIO_SODR = (1 << pin);
	}
}
