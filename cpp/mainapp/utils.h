#ifndef __UTILS_H
#define __UTILS_H

#include "inttypes.h"
#include "fnetwork.h"
#include "Windows.h"

#define SAFEDELETE(a) do{ if(a) {delete a;a=NULL;}}while(0)
#define CHECKVALID(a)			do{ if(!(a)) return;}while(0)
#define UNUSED(a)				do{ a; }while(0)
#define IF(a)							if(a){
#define ELSE							}else{
#define ELSEIF(a)					}else if(a){
#define ENDIF						}
#define THEN(b)						b;}
#define CONDITIONEXE(a,b,c)	( a ) ? ( b ) : ( c )
#define CHECKVALIDRETURN( a, b )  do{ if(!(a)) return (b);}while(0)

namespace Utils
{
	enum SysProperty
	{
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
	};

	enum BitOffset
	{
		BIT_FIRST,
		BIT_MAX = 32,
	};
	void setBit(uint32_t& value,BYTE offset,bool isset);
	void setBit(uint32_t& value,BYTE offsetstart,BYTE offsetfinish,uint32_t countervalue);
	bool getBit(uint32_t value,BYTE offset);
	uint32_t getBit(uint32_t value,BYTE offsetstart,BYTE offsetfinish);
};

#endif