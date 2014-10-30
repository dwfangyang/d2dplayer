#include "utils.h"

void Utils::setBit(uint32_t& value,unsigned short offset,bool isset)
{
	CHECKVALID( offset < BIT_MAX );
	uint32_t mask = 0x1 << offset;
	IF( isset )
		value |= mask;
	ELSE
		value &= ~mask;
	ENDIF
}

void Utils::setBit(uint32_t& value,unsigned byte offsetstart,unsigned byte offsetfinish,uint32_t countervalue)
{
	CHECKVALID( offsetfinish <= BIT_MAX && offsetfinish > offsetstart );
	uint32_t dstmask = (0xffffffff << offsetstart) >> (BIT_MAX-offsetfinish);
	countervalue = ( countervalue << offsetstart ) & dstmask;
	value = value & (~dstmask) | countervalue;
}