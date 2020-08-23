/* Copyright (C) Tor Brodtkorb */

#ifndef CLOCK_H
#define CLOCK_H

#include "sam.h"
#include "types.h"

enum clock_source {
	RC_OCILATOR,
	CRYSTAL_OCILLATOR
};
	
enum master_div {
	NO_DIV,
	DIV2,
	DIV4,
	DIV3
};

enum master_pres {
	NO_PRES,
	PRES_2,
	PRES_4,
	PRES_8,
	PRES_6,
	PRES_32,
	PRES_64,
	PRES_3
};

enum clock_net {
	SLOW_CLK,
	MAIN_CLK,
	PLLA_CLOCK,
	UPLL_CLOCK
};

void clock_source_enable(enum clock_source source, u8 wait_time);

void main_clock_select(enum clock_source source);

void plla_setup(u16 mult, u8 div, u8 wait);

void master_clock_config (enum clock_net net, enum master_pres prescaler, enum master_div division);

void enable_peripheral_clock(u8 pid);

#endif
