/* Copyright (C) Tor Brodtkorb */

#include "sam.h"
#include "startup.h"
#include "types.h"
#include "led_driver.h"
#include "gpio.h"
#include "sleep.h"
#include "print.h"
#include "engine.h"


struct led {
	u8 r; 
	u8 g; 
	u8 b;
};

struct led led_strip[13];
	
void ws2812b_draw(struct led* addr, u32 leds, Pio* port, u32 pin);


struct graphics_engine graphics_engine;

int main(void)
{
	startup();
	
	engine_init(&graphics_engine);
	
	while (1) {
	

	}
}


