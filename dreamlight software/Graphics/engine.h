/// Copyright (C) Tor Brodtkorb

#ifndef ENGINE_H
#define ENGINE_H

#include "print.h"
#include "types.h"
#include "led_driver.h"

struct graphics_engine {
	struct pixel* pixels;
	u32 pixel_cnt;
	
	void (*update)(struct graphics_engine*); 
};


void engine_init(struct graphics_engine* e);

#endif

