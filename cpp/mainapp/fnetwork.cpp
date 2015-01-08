#include "fnetwork.h"

uint16_t FNetWork::pop_uint16(const char* c)
{
	uint16_t ret = 0;
	memmove( &ret, c, 2 );
	return ret;
}

BYTE FNetWork::pop_byte(const char* c)
{
	BYTE b = 0;
	memmove( &b, c, 1);
	return b;
}