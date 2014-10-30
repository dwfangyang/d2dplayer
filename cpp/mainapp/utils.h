#include "inttypes.h"

#define SAFEDELETE(a) do{ if(a) {delete a;a=NULL;}}while(0)
#define CHECKVALID(a)			do{ if(!(a)) return;}while(0)
#define UNUSED(a)				do{ a; }while(0)
#define IF(a)							if(a){
#define ELSE							}else{
#define ELSEIF(a)					}else if(a){
#define ENDIF						}
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

class Utils
{
public:
	static void setBit(uint32_t& value,unsigned byte offset,bool isset);
	static void setBit(uint32_t& value,unsigned byte offsetstart,unsigned byte offsetfinish,uint32_t countervalue);
};