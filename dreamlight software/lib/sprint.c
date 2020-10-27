#include "sprint.h"

#define FMT_EX   0x01
#define FMT_STAR 0x02

static inline u8 char_to_num(char c)
{
	return (u8)(c - '0');
}

static inline u8 is_num(char c)
{
	return ((c >= '0') && (c <= '9')) ? 1 : 0;
}

u32 vsprint(char* buf, const char* data, va_list args)
{
	const char* start = buf;
	for (; *data; ++data) {
		
		if (*data != '%') {
			*buf++ = *data;
			continue;
		}

		u8 flags = 0;
		while (1) {
			data++;
			if (*data == '!') {
				flags |= FMT_EX;
				data++;
			} else if (*data == '*') {
				flags |= FMT_STAR;
				data++;
			} else {
				break;
			}
		}
		
		/* Get the format number */
		u32 num = 0;
		while (is_num(*data)) {
			num = (num * 10) + char_to_num(*data);
			data++;
		}
		
		/* Process commands */
		switch (*data) {
			case 's':{
				const char* src = va_arg(args, char*);
				while(num--) {
					*buf++ = *src++;
				} break;
			}
		}
		
	}
	return buf - start;
}
