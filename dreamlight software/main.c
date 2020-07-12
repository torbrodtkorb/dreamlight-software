/// Copyright (C) Tor Brodtkorb

#include "sam.h"
#include "gpio.h"
#include "systick.h"


int main(void) {
	gpio_set_function(PIOC, 8, FUNCTION_GPIO);
	gpio_set_direction(PIOC, 8, GPIO_OUTPUT);
	gpio_clear(PIOC, 8);
	
	systick_set_rvr(12000);
	systick_enable();
	systick_interrupt_enable();
	asm volatile("cpsie f" : : : "memory");
	
    while (1) {
    }
	
}

void SysTick_Handler(void) {
	gpio_toggle(PIOC, 8);
}