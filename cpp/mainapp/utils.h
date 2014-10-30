#include "inttypes.h"
#include "Windows.h"

#define SAFEDELETE(a) do{ if(a) {delete a;a=NULL;}}while(0)
#define CHECKVALID(a)			do{ if(!(a)) return;}while(0)
#define UNUSED(a)				do{ a; }while(0)
#define IF(a)							if(a){
#define ELSE							}else{
#define ELSEIF(a)					}else if(a){
#define ENDIF						}
#define THEN(b)						b;}
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
	static void setBit(uint32_t& value,BYTE offset,bool isset);
	static void setBit(uint32_t& value,BYTE offsetstart,BYTE offsetfinish,uint32_t countervalue);
	static bool getBit(uint32_t value,BYTE offset);
	static uint32_t getBit(uint32_t value,BYTE offsetstart,BYTE offsetfinish);
};