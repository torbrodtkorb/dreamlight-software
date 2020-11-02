/// Copyright (C) Tor Brodtkorb

#include "engine.h"
#include "gmalloc.h"

void engine_update(struct graphics_engine* g)
{
	print("stram string\n");
}

void engine_init(struct graphics_engine* e)
{
	print("Graphics engine started\n");
	
	e->pixel_cnt = 50;
	e->pixels = gmalloc(50 * sizeof(struct pixel));
	e->update = engine_update;

}
