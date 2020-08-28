/* Copyright (C) Tor Brodtkorb */

#include "led_strip.h"
#include "clock.h"
#include "gpio.h"
#include "spi.h"

struct pixel pixels[NUMBER_OF_LEDS] = {0};
int i = 0;

void led_strip_init(void)
{
	
	
	/* Enable peripheral clock on spi_1 */
	enable_peripheral_clock(21);
	
	gpio_set_function(PIOD,21, FUNCTION_B);
	gpio_set_function(PIOD,20, FUNCTION_B);
	gpio_set_function(PIOD,22, FUNCTION_B);
	gpio_set_function(PIOD,25, FUNCTION_B);
	
	struct spi_desc desc = {
		.delay_between_chip_select = 10,
		.cs = 1,
		.master_mode_enable = 1,
		.delay_between_consecutive_transfers = 10,
		.delay_between_falling_edge = 10,
		.pck_div = 200,
		.bit_per_transfer = SPI_8_BIT,
		.clock_phase = SPI_CLOCK_CAPTURE_ON_TRAILING,
		.clock_polarity = SPI_CLOCK_INACTIVE_LOW,
	};
	
	spi_init(SPI0, &desc);
	
}
/*
void led_on (u8 global, u8 red, u8 green,u8 blue){
	color[5] = (pixel){global, red, green, blue};
	spi_transmit_8_bit()
		
}
*/

void led_strip_on (u8 global, u8 red, u8 green,u8 blue){
	
	spi_transmit_8_bit(SPI0, 0x00);
	spi_transmit_8_bit(SPI0, 0x00);
	spi_transmit_8_bit(SPI0, 0x00);
	spi_transmit_8_bit(SPI0, 0x00);
	
	for (int i = 0; i < NUMBER_OF_LEDS; i ++){
		pixels[i].blue = 0;
		pixels[i].red = 0;
		pixels[i].green = 0;
		pixels[i].global = 0;
	}
				
	for (int i = 0; i < 104; i ++){
		//color[i] = (struct pixel){global, red, green, blue};
		
		pixels[i].blue = blue;
		pixels[i].red = red;
		pixels[i].green = green;
		pixels[i].global = global;
			
		spi_transmit_8_bit(SPI0, pixels[i].global | (0b111 << 5));
		spi_transmit_8_bit(SPI0, pixels[i].red);
		spi_transmit_8_bit(SPI0, pixels[i].green);
		spi_transmit_8_bit(SPI0, pixels[i].blue);
	}

	spi_transmit_8_bit(SPI0, 0xFF);
	spi_transmit_8_bit(SPI0, 0xFF);
	spi_transmit_8_bit(SPI0, 0xFF);
	spi_transmit_8_bit(SPI0, 0xFF);
}

void led_strip_on_to (u8 pixel, u8 global, u8 red, u8 green,u8 blue){
	
	spi_transmit_8_bit(SPI0, 0x00);
	spi_transmit_8_bit(SPI0, 0x00);
	spi_transmit_8_bit(SPI0, 0x00);
	spi_transmit_8_bit(SPI0, 0x00);	
	
		for (int i = 0; i < NUMBER_OF_LEDS; i ++){
			pixels[i].blue = 0;
			pixels[i].red = 0;
			pixels[i].green = 0;
			pixels[i].global = 0;
		}
		pixels[pixel-1] = (struct pixel){global, red, green, blue};

	
	
	for (int i = 0; i < NUMBER_OF_LEDS; i ++){
		
		spi_transmit_8_bit(SPI0, pixels[i].global | (0b111 << 5));
		spi_transmit_8_bit(SPI0, pixels[i].red);
		spi_transmit_8_bit(SPI0, pixels[i].green);
		spi_transmit_8_bit(SPI0, pixels[i].blue);
	}

	spi_transmit_8_bit(SPI0, 0xFF);
	spi_transmit_8_bit(SPI0, 0xFF);
	spi_transmit_8_bit(SPI0, 0xFF);
	spi_transmit_8_bit(SPI0, 0xFF);
}