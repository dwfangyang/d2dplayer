#ifndef _FNETWORK
#define _FNETWORK

#include <winsock.h>
#include "inttypes.h"

namespace FNetWork
{
	enum ProtoMaxType
	{
		MAXTYPE_NONE,
		MAXTYPE_D2D,
	};
	BYTE pop_byte(const char* c);
	uint16_t pop_uint16(const char* c);
}

#endif