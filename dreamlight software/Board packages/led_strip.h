/* Copyright (C) Tor Brodtkorb */

#ifndef LED_STRIP_H
#define LED_STRIP_H
#define NUMBER_OF_LEDS 105

#include "sam.h"
#include "types.h"

void led_strip_init(void);

struct pixel {
	u8 global : 5;
	u8 red;
	u8 green;
	u8 blue;
};

void led_on (u8 global, u8 red, u8 green,u8 blue);

void led_strip_on (u8 global, u8 red, u8 green,u8 blue);

void led_strip_on_to (u8 pixel, u8 global, u8 red, u8 green,u8 blue);

void update_led_strip(struct pixel data[], u8 lenght);




#endif