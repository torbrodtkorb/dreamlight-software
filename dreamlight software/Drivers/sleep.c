/* Copyright (C) Tor Brodtkorb */

#include "sam.h"
#include "sleep.h"
#include "systick.h"

static volatile u32 tick = 0;

void sleep_init(void)
{
	systick_set_rvr(300000);
	systick_enable();
	systick_interrupt_enable();
}

void sleep(u32 ms){
	tick = 0;
	while (tick < ms);
}

void SysTick_Handler(void)
{
	/* Is Called every time SysTick reloads */
	tick++;
}
