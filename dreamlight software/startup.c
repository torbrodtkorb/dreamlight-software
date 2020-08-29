/* Copyright (C) Tor Brodtkorb */

#include "startup.h"

#include "sam.h"
#include "gpio.h"
#include "systick.h"
#include "clock.h"
#include "watchdog.h"
#include "flash.h"
#include "usart.h"
#include "print.h"
#include "spi.h"
#include "led_driver.h"
#include "sleep.h"

void startup(void)
{
	watchdog_disable();
	flash_set_accsess_cycles(7);
	clock_source_enable(CRYSTAL_OCILLATOR, 0xFF);
	main_clock_select(CRYSTAL_OCILLATOR);
	plla_setup(25, 1, 0xFF);
	master_clock_config(PLLA_CLOCK, NO_PRES, DIV2);
	sleep_init();
	gpio_set_function(PIOC, 8, FUNCTION_GPIO);
	gpio_set_direction(PIOC, 8, GPIO_OUTPUT);
	gpio_clear(PIOC, 8);
	/* Enables all interrupt on the chip */
	asm volatile("cpsie f" : : : "memory");
	print_init();
	led_strip_init();
}