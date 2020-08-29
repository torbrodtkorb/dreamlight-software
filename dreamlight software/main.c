/* Copyright (C) Tor Brodtkorb */

#include "sam.h"
#include "startup.h"
#include "types.h"
#include "led_driver.h"
#include "gpio.h"
#include "sleep.h"

#define NUMBER_OF_LEDS 105

static struct pixel pixels[NUMBER_OF_LEDS] = {0};

void animation(void){
	for (u32 i = 0; i < NUMBER_OF_LEDS; i++){
		pixels[i].global = 1;
		pixels[i].blue = 255;
		update_led_strip(pixels, NUMBER_OF_LEDS);
		sleep(1);
	}
}

void test(void)
{
	for (u32 i = 0; i < NUMBER_OF_LEDS; i++) {
		pixels[i].global = 5;
		pixels[i].green = 5;
		pixels[i].red = 0;
		pixels[i].blue = 0;
	}
	update_led_strip(pixels, NUMBER_OF_LEDS);
	sleep(300);
	for (u32 i = 0; i < NUMBER_OF_LEDS; i++) {
		pixels[i].global = 5;
		pixels[i].green = 0;
		pixels[i].red = 0;
		pixels[i].blue = 5;
	}
	update_led_strip(pixels, NUMBER_OF_LEDS);
	sleep(300);
}

int main(void)
{
	startup();
	
	pixels[0].global = 5;
	pixels[0].red = 200;
	
	//update_led_strip(pixels, NUMBER_OF_LEDS);
	//animation();
	
    while (1) {
		animation();
    }
}


