#include <string>
#include "inttypes.h"
#include "Windows.h"
using namespace std;

class FString
{
	enum Bit{
		BIT_
	};
public:
	FString();
	FString( LPCSTR p );
	FString( LPWCH wp );
	~FString();
	string toStdString();
	wstring toStdWString(); 
private:
	void stdtostdw();
private:
	uint32_t		m_uFlag;		//最高位标识str or wstr,次高位代表是否为new,余下30位代表长度
	void*			m_pStr;
};
