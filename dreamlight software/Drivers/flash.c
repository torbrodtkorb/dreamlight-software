/// Copyright (C) Tor Brodtkorb

#include "flash.h"
#include "types.h"
#include "sam.h"

void flash_set_accsess_cycles(u8 cycles) {
	
	u32 reg = EFC->EEFC_FMR;
	reg &= ~(0b1111 << 8);
	reg |= (((cycles - 1) & 0b1111) << 8);
	EFC->EEFC_FMR = reg;
}
