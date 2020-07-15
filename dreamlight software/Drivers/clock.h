/// Copyright (C) Tor Brodtkorb

#ifndef CLOCK_H
#define CLOCK_H

#include "sam.h"
#include "types.h"

enum clock_source {
	RC_OCILATOR,
	CRYSTAL_OCILLATOR
};
	
enum master_division {
	NO_DIV,
	DIV2,
	DIV4,
	DIV3
};

enum processor_prescaler {
	NO_PRESCALER,
	PRESCALER1,
	PRESCALER2,
	PRESCALER4,
	PRESCALER8,
	PRESCALER16,
	PRESCALER32,
	PRESCALER64,
	PRESCALER3
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

void master_clock_config (enum clock_net net, enum processor_prescaler prescaler, enum master_division division);

#endif