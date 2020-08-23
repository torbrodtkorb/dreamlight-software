/* Copyright (C) Tor Brodtkorb */

#ifndef SPI_H
#define SPI_H

#include "sam.h"
#include "types.h"
	
enum spi_bit_per_transfer {
	SPI_8_BIT,
	SPI_9_BIT,
	SPI_10_BIT,
	SPI_11_BIT,
	SPI_12_BIT,
	SPI_13_BIT,
	SPI_14_BIT,
	SPI_15_BIT,
	SPI_16_BIT,
};
	
enum spi_clock_phase {
	SPI_CLOCK_CAPTURE_ON_TRAILING,
	SPI_CLOCK_CAPTURE_ON_LEADING
};

enum spi_clock_polarity {
	SPI_CLOCK_INACTIVE_LOW,
	SPI_CLOCK_INACTIVE_HIGH
};

struct spi_desc {
	u8 delay_between_chip_select;
	u8 cs     : 2;
	u8 master_mode_enable : 1;
	
	u8 delay_between_consecutive_transfers;
	u8 delay_between_falling_edge;
	u8 pck_div;
	enum spi_bit_per_transfer bit_per_transfer;
	enum spi_clock_phase clock_phase;
	enum spi_clock_polarity clock_polarity;
};

void spi_init(Spi* hw, struct spi_desc* desc);

void spi_transmit_8_bit(Spi* hw, u8 data);


#endif
