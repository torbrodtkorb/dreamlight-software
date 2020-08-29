/* Copyright (C) Tor Brodtkorb */

#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "sam.h"
#include "types.h"

struct pixel {
	u8 global : 5;
	u8 red;
	u8 green;
	u8 blue;
};

void led_strip_init(void);

void update_led_strip(const struct pixel* data, u32 lenght);

#endif