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
	while(!(PMC->PMC_SR & (1 << 16)));
}

void plla_setup(u16 mult, u8 div, u8 wait) {
	u32 reg = (1 << 29);
	reg |= ((0x7FF & mult) << 16);
	reg |= ((0x3F & wait) << 8);
	reg |= div;
	PMC->CKGR_PLLAR = reg;
	while (!(PMC->PMC_SR & (1 << 1)));
}

void master_clock_config (enum clock_net net, enum processor_prescaler prescaler, enum master_division division) {
	u32 reg = PMC->PMC_MCKR;
	reg &= ~(0b111 << 4);
	reg |= (prescaler << 4);
	PMC->PMC_MCKR |= reg;
	while (!(PMC->PMC_SR & (1 << 3)));
	
	reg = PMC->PMC_MCKR;
	reg &= ~(0b11 << 8);
	reg |= (division << 8);
	PMC->PMC_MCKR |= reg;
	while (!(PMC->PMC_SR & (1 << 3)));
	
	reg = PMC->PMC_MCKR;
	reg &= ~(0b11 << 0);
	reg |= (net << 0);
	PMC->PMC_MCKR |= reg;
	while (!(PMC->PMC_SR & (1 << 3)));
	
}