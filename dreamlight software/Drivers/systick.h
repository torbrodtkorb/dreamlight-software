/* Copyright (C) Tor Brodtkorb */

#ifndef SYSTICK_H
#define SYSTICK_H

#include "sam.h"

static inline void systick_enable(void)
{
	/* Enables SysTick and clock source (processor clock) */
	SysTick->CTRL |= (1 << 0) | (1 << 2);
}

static inline void systick_interrupt_enable(void)
{
	/* Enables SysTick exception request */
	SysTick->CTRL |= (1 << 1);
}

static inline void systick_set_rvr(u32 reload_value)
{
	/* Set reload value */
	SysTick->LOAD = reload_value & 0xffffff;
}

#endif
