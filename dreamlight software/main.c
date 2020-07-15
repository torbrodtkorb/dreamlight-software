/// Copyright (C) Tor Brodtkorb

#include "sam.h"
#include "gpio.h"
#include "systick.h"
#include "clock.h"

volatile u32 tick = 0;

void delay_ms(u32 ms) {
	tick = 0;
	while (tick < ms);
}

int main(void) {
	gpio_set_function(PIOC, 8, FUNCTION_GPIO);
	gpio_set_direction(PIOC, 8, GPIO_OUTPUT);
	gpio_clear(PIOC, 8);
	
	
	clock_source_enable();
	
	
	systick_set_rvr(12000);
	systick_enable();
	systick_interrupt_enable();
	/* Enables all intrrupt on the chip */
	asm volatile("cpsie f" : : : "memory");
	
    while (1) {
		delay_ms(500);
		gpio_toggle(PIOC, 8);
    }
}

void SysTick_Handler(void) {
	/* Is Called every time SysTick reloads */
	tick++;
}