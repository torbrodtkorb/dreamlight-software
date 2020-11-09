/* Copyright (C) Tor Brodtkorb */

#ifndef FPU_H
#define FPU_H

#include "types.h"

static inline void fpu_init(void)
{
	*(volatile u32*)0xE000ED88 = (0xF << 20);

}

#endif