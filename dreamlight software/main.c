/* Copyright (C) Tor Brodtkorb */

#include "sam.h"
#include "startup.h"
#include "types.h"
#include "led_driver.h"
#include "gpio.h"
#include "sleep.h"
#include "print.h"



char* nam = "truse";

struct led {
	u8 r; 
	u8 g; 
	u8 b;
};

struct led led_strip[2];
	
void ws2812b_draw(struct led* addr, u32 leds, Pio* port, u32 pin);

int main(void)
{
	startup();
	gpio_set_function(PIOD,22, FUNCTION_GPIO);
	gpio_set_direction(PIOD,22, GPIO_OUTPUT);
	led_strip[0] = (struct led) {0b01010000, 0b00101111, 0b11111111};
	led_strip[1] = (struct led) {0b01010000, 0b00101111, 0b11111111};
    while (1) {
		ws2812b_draw(led_strip, 1, PIOD, 22);
    }
}


