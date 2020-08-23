/* Copyright (C) Tor Brodtkorb */

#include "led_strip.h"
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
		.use_cs = 0,
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