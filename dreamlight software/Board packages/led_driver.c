/* Copyright (C) Tor Brodtkorb */

#include "led_driver.h"
#include "clock.h"
#include "gpio.h"
#include "spi.h"

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
		.delay_between_consecutive_transfers = 1,
		.delay_between_falling_edge = 10,
		.pck_div = 10,
		.bit_per_transfer = SPI_8_BIT,
		.clock_phase = SPI_CLOCK_CAPTURE_ON_LEADING,
		.clock_polarity = SPI_CLOCK_INACTIVE_LOW,
	};
	
	spi_init(SPI0, &desc);
	
}

void update_led_strip(const struct pixel* data, u32 lenght)
{
	for (u8 i = 0; i < 4; i++) {
		spi_transmit_8_bit(SPI0, 0x00);
	}

	for (u32 i = 0; i < lenght; i++) {
		spi_transmit_8_bit(SPI0, data->global | (0b111 << 5));
		spi_transmit_8_bit(SPI0, data->blue);
		spi_transmit_8_bit(SPI0, data->green);
		spi_transmit_8_bit(SPI0, data->red);
		
		data++;
	}

	for (u8 i = 0; i < 4; i++) {
		spi_transmit_8_bit(SPI0, 0xFF);
		spi_transmit_8_bit(SPI0, 0xFF);
	}
}
