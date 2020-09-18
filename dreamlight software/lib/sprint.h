/* Copyright (C) Tor Brodtkorb */

#ifndef SPRINT_H
#define SPRINT_H

#include "types.h"
#include <stdarg.h>

u32 vsprint(char* buf, const char* data, va_list args);

#endif