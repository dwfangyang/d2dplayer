#ifndef _FSTRING
#define _FSTRING

#include <string>
#include "inttypes.h"
#include "utils.h"
using namespace std;

class FString
{
	enum Bit{
		BIT_SPARED = 2,
		BIT_NEWED = 30,
		BIT_STRTYPE,
	};
public:
	FString();
	FString( LPCSTR p );
	FString( LPWCH wp );
	~FString();
	string toStdString();
	wstring toStdWString(); 
private:
	string getLastErrorStr();
private:
	uint32_t		m_uFlag;		//最高位标识str or wstr,次高位代表是否为new,余下30位代表new出来的长度
	void*			m_pStr;
	string		m_sErr;
};

#endif