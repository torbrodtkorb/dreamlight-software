/* Copyright (C) Tor Brodtkorb */

#include "sam.h"
#include "gpio.h"
#include "systick.h"
#include "clock.h"
#include "watchdog.h"
#include "flash.h"
#include "usart.h"
#include "print.h"
#include "spi.h"
#include "led_strip.h"

volatile u32 tick = 0;

void delay_ms(u32 ms)
{
	tick = 0;
	while (tick < ms);
}

int main(void)
{
	watchdog_disable();
	
	flash_set_accsess_cycles(7);
	
	clock_source_enable(CRYSTAL_OCILLATOR, 0xFF);
	main_clock_select(CRYSTAL_OCILLATOR);
	plla_setup(25, 1, 0xFF);
	master_clock_config(PLLA_CLOCK, NO_PRES, DIV2);
	
	
	gpio_set_function(PIOC, 8, FUNCTION_GPIO);
	gpio_set_direction(PIOC, 8, GPIO_OUTPUT);
	gpio_clear(PIOC, 8);
	
	systick_set_rvr(300000);
	systick_enable();
	systick_interrupt_enable();
	/* Enables all interrupt on the chip */
	asm volatile("cpsie f" : : : "memory");
	
	
	print_init();
	
	led_strip_init();
	
	while (1) {
		spi_transmit_8_bit(SPI0, 0b11100010);
	}
	
    while (1) {
		delay_ms(500);
		gpio_toggle(PIOC, 8);
		printl("stram");
		
    }
}








void SysTick_Handler(void)
{
	/* Is Called every time SysTick reloads */
	tick++;
}
