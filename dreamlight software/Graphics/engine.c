/// Copyright (C) Tor Brodtkorb

#include "engine.h"
#include "gmalloc.h"

void engine_update(struct graphics_engine* e)
{
	led_strip_update(e->pixels, e->pixel_cnt);
}

void engine_init(struct graphics_engine* e)
{
	print("Graphics engine started\n");
	
	e->pixel_cnt = 50;
	e->pixels = gmalloc(50 * sizeof(struct pixel));
	e->update = engine_update;
	
	// Initialize the led strip
	struct pixel* p = e->pixels;
	
	for (u32 i = 0; i < e->pixel_cnt; i++) {
		p->global = 16;
		p->red = 0;
		p->green = 0;
		p->blue = 0;
		p++;
	}
	e->update(e);
}
