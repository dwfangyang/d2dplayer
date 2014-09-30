#define SAFEDELETE(a) do{ if(a) {delete a;a=NULL;}}while(0)
enum SysProperty
{
	SCREEN_WIDTH,
	SCREEN_HEIGHT,
};