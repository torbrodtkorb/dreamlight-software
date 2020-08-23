/* Copyright (C) Tor Brodtkorb */

#ifndef USART_H
#define USART_H

#include "sam.h"
#include "types.h"

enum usart_parity {
	USART_EVEN,
	USART_ODD,
	USART_NONE = 4
};

enum usart_stop_bit {
	USART_STOP_BIT_1,
	USART_STOP_BIT_2 = 2
};

enum usart_data_bits {
	USART_DATA_5,
	USART_DATA_6,
	USART_DATA_7,
	USART_DATA_8
};

struct usart_desc {
	u32 baudrate;
	enum usart_parity parity;
	enum usart_stop_bit stop_bits;
	enum usart_data_bits data_bits;			
};

void usart_init(Usart* usart, struct usart_desc* desc);

static inline void usart_transmit(Usart* usart, u8 data)
{
	/* Wait to the US_THR is empty */
	while (!(usart->US_CSR & (1 << 1)));
	
	/* Load transmit Holding Register */
	usart->US_THR = data;
}

#endif
