/* Copyright (C) Tor Brodtkorb */

#ifndef PRINT_H
#define PRINT_H

#include <stdarg.h>

void print_init(void);

void _print(const char* data, ...);

void print(const char* data);

#endif
