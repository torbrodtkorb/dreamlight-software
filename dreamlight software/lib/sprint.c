#include "sprint.h"

u32 vsprint(char* buf, const char* data, va_list args)
{
	const char* start = buf;
	while (*data){
		*buf = *data;
		buf++;
		data++;
	}
	return buf - start;
}
