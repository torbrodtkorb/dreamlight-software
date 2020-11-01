/// Copyright (C) Tor Brodtkorb

#ifndef ENGINE_H
#define ENGINE_H

#include "print.h"
#include "types.h"

struct graphics_engine {
	void (*print)(const char*);
	
	u32* tmp;
};


void engine_init(struct graphics_engine* e);

#endif
