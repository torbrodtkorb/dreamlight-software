/* Copyright (C) Tor Brodtkorb */

#include "sam.h"
#include "startup.h"
#include "types.h"
#include "led_driver.h"
#include "gpio.h"
#include "sleep.h"

#define NUMBER_OF_LEDS 105

static struct pixel pixels[NUMBER_OF_LEDS] = {0};

void simple_led (void){
	for (u32 i = 0; i < NUMBER_OF_LEDS; i++){
		pixels[i].global = 1;
		pixels[i].blue = 255;
		pixels[i-1].blue = 0;
		update_led_strip(pixels, NUMBER_OF_LEDS);
		sleep(1);
	}
	for (i32 i = NUMBER_OF_LEDS; i > 0; i--){
		pixels[i].global = 1;
		pixels[i].blue = 255;
		pixels[i+1].blue = 0;
		update_led_strip(pixels, NUMBER_OF_LEDS);
		sleep(1);
	}
	
}
void animation(void){
	for (i32 i = 0; i < NUMBER_OF_LEDS; i++){
		pixels[i].global = 1;
		pixels[i].blue = 255;
		update_led_strip(pixels, NUMBER_OF_LEDS);
		sleep(1);
	}
}

void test(void)
{
	for (u32 i = 0; i < NUMBER_OF_LEDS; i++) {
		pixels[i].global = 31;
		pixels[i].green = 5;
		pixels[i].red = 0;
		pixels[i].blue = 0;
	}
	update_led_strip(pixels, NUMBER_OF_LEDS);
	sleep(300);
	for (u32 i = 0; i < NUMBER_OF_LEDS; i++) {
		pixels[i].global = 31;
		pixels[i].green = 0;
		pixels[i].red = 0;
		pixels[i].blue = 5;
	}
	update_led_strip(pixels, NUMBER_OF_LEDS);
	sleep(300);
}


void fun_light (void){
	for (u32 i = (NUMBER_OF_LEDS - 1)/2; i < NUMBER_OF_LEDS; i++){
		pixels[i].global = 31;
		pixels[i].green = 204;
		pixels[i].red = 0;
		pixels[i].blue = 204;
		
		pixels[NUMBER_OF_LEDS - i - 1].global = 31;
		pixels[NUMBER_OF_LEDS - i - 1].green = 204;
		pixels[NUMBER_OF_LEDS - i - 1].red = 0;
		pixels[NUMBER_OF_LEDS - i - 1].blue = 204;
		
		update_led_strip(pixels, NUMBER_OF_LEDS);
		//sleep(10);	
	}
	
	for (i32 i = NUMBER_OF_LEDS; i > (NUMBER_OF_LEDS - 1)/2; i--){
		pixels[i].global = 31;
		pixels[i].green = 0;
		pixels[i].red = 255;
		pixels[i].blue = 255;
		
		pixels[NUMBER_OF_LEDS - i - 1].global = 31;
		pixels[NUMBER_OF_LEDS - i - 1].green = 0;
		pixels[NUMBER_OF_LEDS - i - 1].red = 255;
		pixels[NUMBER_OF_LEDS - i - 1].blue = 255;
		
		update_led_strip(pixels, NUMBER_OF_LEDS);
		//sleep(10);
	}
	
	for (u32 i = (NUMBER_OF_LEDS - 1)/2; i < NUMBER_OF_LEDS; i++){
		pixels[i].global = 31;
		pixels[i].green = 170;
		pixels[i].red = 33;
		pixels[i].blue = 33;
		
		pixels[NUMBER_OF_LEDS - i - 1].global = 31;
		pixels[NUMBER_OF_LEDS - i - 1].green = 170;
		pixels[NUMBER_OF_LEDS - i - 1].red = 33;
		pixels[NUMBER_OF_LEDS - i - 1].blue = 33;
		
		update_led_strip(pixels, NUMBER_OF_LEDS);
		//sleep(10);
	}


	for (i32 i = NUMBER_OF_LEDS; i > (NUMBER_OF_LEDS - 1)/2; i--){
		pixels[i].global = 31;
		pixels[i].green = 150;
		pixels[i].red = 255;
		pixels[i].blue = 0;
		
		pixels[NUMBER_OF_LEDS - i - 1].global = 31;
		pixels[NUMBER_OF_LEDS - i - 1].green = 150;
		pixels[NUMBER_OF_LEDS - i - 1].red = 255;
		pixels[NUMBER_OF_LEDS - i - 1].blue = 0;
		
		update_led_strip(pixels, NUMBER_OF_LEDS);
		//sleep(10);
	}
}




int main(void)
{
	startup();
	

	
	//update_led_strip(pixels, NUMBER_OF_LEDS);
	//animation();
	
    while (1) {
		/*
		for (u32 i = 0; i < NUMBER_OF_LEDS; i++){
		pixels[i].global = 0;
		pixels[i].green = 0;
		pixels[i].red = 0;
		pixels[i].blue = 0;
		}
		
		update_led_strip(pixels, NUMBER_OF_LEDS);
		*/
		//simple_led();
		spi_transmit_8_bit(SPI0, 0b00011101);
    }
}


