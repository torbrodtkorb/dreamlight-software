/// Copyright (C) Tor Brodtkorb

#ifndef SPI_H
#define SPI_H

struct spi_desc{
	u8 data_bit;
	u8 bit_rate;
	u8 clock_phase;
	
	};


void spi_init(Spi* hardware, struct spi_desc* desc);


#endif