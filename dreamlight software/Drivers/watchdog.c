/// Copyright (C) Tor Brodtkorb

#include "watchdog.h"
#include "sam.h"

void watchdog_disable(void) {
	/*
	 * While writing WDDIS bit, WDV an
	 * WDT can only be written to once WDD must not be modified
	 */
	WDT->WDT_MR |= (1 << 15);
}