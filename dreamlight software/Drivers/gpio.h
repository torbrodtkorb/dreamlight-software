/* Copyright (C) Tor Brodtkorb */

#ifndef GPIO_H
#define GPIO_H

#include "sam.h"
#include "types.h"

enum gpio_function {
	FUNCTION_A,
	FUNCTION_B,
	FUNCTION_C,
	FUNCTION_D,
	FUNCTION_GPIO
};

enum gpio_dir {
	GPIO_INPUT,
	GPIO_OUTPUT
};

void gpio_set_function(Pio* port, u8 pin, enum gpio_function func);

void gpio_set_direction(Pio* port, u8 pin, enum gpio_dir dir);

void gpio_set(Pio* port, u8 pin);

void gpio_clear(Pio* port, u8 pin);

void gpio_toggle(Pio* port, u8 pin);

#endif
