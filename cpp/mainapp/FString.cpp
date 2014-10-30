#include "FString.h"

FString::FString():m_pStr(NULL),m_uFlag(0)
{

}

FString::FString( LPCSTR p ):m_uFlag(0)
{	
	m_pStr = (void *)p;
}

FString::~FString()
{

}

string FString::toStdString()
{
	LPWSTR wp = NULL;
	int len = MultiByteToWideChar(CP_ACP,0,p,-1,wp,0);
	if ( len > 0 )
	{
		wp = new WCHAR[len];
		MultiByteToWideChar(CP_ACP,0,p,-1,wp,len);
	}
	else if( !len )
	{
		switch( GetLastError() )
		{
			case ERROR_INSUFFICIENT_BUFFER:
				"buffer size not enough";
				break;
			case ERROR_INVALID_FLAGS:
				"dwFlags not invalid";
				break;
			case ERROR_INVALID_PARAMETER:
				"any parameter invalid";
				break;
			case ERROR_NO_UNICODE_TRANSLATION:
				"invalid unicode character in src str";
				break;
		}
	}
	return "";
}

void FString::stdtostdw()
{

}