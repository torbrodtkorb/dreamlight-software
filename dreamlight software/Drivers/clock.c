/// Copyright (C) Tor Brodtkorb

#include "clock.h"

void clock_source_enable(enum clock_source source, u8 wait_time) {
	if (source == RC_OCILATOR) {
		PMC->CKGR_MOR |= (1 << 3) | 0x370000;
		/* Wait to the clock is stable */
		while (!(PMC->PMC_SR & (1 << 17)));
	}
	else {
		/* MOSCXTBY must be cleared to enable crystal oscillator */
		u32 reg = PMC->CKGR_MOR;
		reg &= ~((1 << 1) | (0xFF << 8));
		reg |= (1 << 0) | (wait_time << 8);
		PMC->CKGR_MOR = reg | 0x370000;
		/* Wait to the clock is stable */
		while (!(PMC->PMC_SR & (1 << 0)));
	}
}

void main_clock_select(enum clock_source source) {
	if (source == RC_OCILATOR) {
		/* Choose RC oscillator to be main clock */
		PMC->CKGR_MOR &= ~(1 << 24);
	}
	else {
		/* Choose external oscillator to be main clock */
		PMC->CKGR_MOR |= (1 << 24);
	}
	/* Wait to ensure the switch is complete */
	while(!(PMC->PMC_SR & (1 << 16)));
}

void plla_setup(u16 mult, u8 div, u8 wait) {
	/* Bit 29 must always be set to ‘1’ when programming the CKGR_PLLAR */
	u32 reg = (1 << 29);
	/* Set value for multiplier, division and wait */
	reg |= ((0x7FF & mult) << 16);
	reg |= ((0x3F & wait) << 8);
	reg |= div;
	PMC->CKGR_PLLAR = reg;
	/* wait the number of SLCK cycles before PLLA is stable */
	while (!(PMC->PMC_SR & (1 << 1)));
}

void master_clock_config (enum clock_net net, enum master_pres pres, enum master_div div) {
	/* Choose prescaler number */
	u32 reg = PMC->PMC_MCKR;
	reg &= ~(0b111 << 4);
	reg |= (pres << 4);
	PMC->PMC_MCKR |= reg;
	while (!(PMC->PMC_SR & (1 << 3)));
	
	/* Choose division number */
	reg = PMC->PMC_MCKR;
	reg &= ~(0b11 << 8);
	reg |= (div << 8);
	PMC->PMC_MCKR |= reg;
	while (!(PMC->PMC_SR & (1 << 3)));
	
	/* Choose clock net */
	reg = PMC->PMC_MCKR;
	reg &= ~(0b11 << 0);
	reg |= (net << 0);
	PMC->PMC_MCKR |= reg;
	while (!(PMC->PMC_SR & (1 << 3)));
}