/* Copyright (C) Tor Brodtkorb */

#include "spi.h"

void spi_init(Spi* hw, struct spi_desc* desc)
{
	/*
	 * disabled local loopback path
	 * disabled wait date read before transfer
	 * disabled chip select decode
	 * Enabled Fixed peripheral
	 */
	u32 reg =	(desc->delay_between_chip_select << 24) |
				(desc->fixed_cs << 16) |
				/* Disable mode fault detection */
				(1 << 4) |
				(desc->master_mode_enable << 0);
				
	hw->SPI_MR = reg;
	
	reg =	(desc->delay_between_consecutive_transfers << 24) |
			(desc->delay_between_falling_edge << 16) |
			(desc->bit_rate << 8) |
			(desc->bit_per_transfer << 4) |
			/* The Peripheral Chip Select Line does not rise after the last transfer is achieved */
			(1 << 3) |
			(desc->clock_phase << 1) |
			(desc->clock_polarity << 0);
			
	hw->SPI_CSR[desc->chip_select];
	
	/* Enable spi */
	hw->SPI_CR = (1 << 0);
}

void spi_transmit_8_bit(Spi* hw, u8 data)
{
	while (!(hw->SPI_SR & (1 << 9)));
	hw->SPI_TDR = data;
}
