/* Copyright (C) Tor Brodtkorb */

#ifndef SPI_H
#define SPI_H

#include "sam.h"
#include "types.h"

enum spi_fixed_chip_select {
	SPI_FIXED_CS_0		= 0b1110,
	SPI_FIXED_CS_1		= 0b1101,
	SPI_FIXED_CS_2		= 0b1011,
	SPI_FIXED_CS_3		= 0b0111,
	SPI_FIXED_CS_NONE	= 0b111
	};
	
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
	
enum spi_chip_select {
	SPI_CHIP_SELECT_0,
	SPI_CHIP_SELECT_1,
	SPI_CHIP_SELECT_2,
	SPI_CHIP_SELECT_3
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
	spi_fixed_chip_select fixed_cs;
	u8 master_mode_enable : 1;
	
	u8 delay_between_consecutive_transfers;
	u8 delay_between_falling_edge;
	u8 bit_rate;
	spi_bit_per_transfer bit_per_transfer;
	enum spi_clock_phase clock_phase;
	enum spi_clock_polarity clock_polarity;
	spi_chip_select chip_select;
	};

void spi_init(Spi* hw, struct spi_desc* desc);

void spi_transmit_8_bit(Spi* hw, u8 data);


#endif
