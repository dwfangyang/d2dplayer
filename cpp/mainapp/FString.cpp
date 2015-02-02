#include "FString.h"
#include "utils.h"
#include "math.h"

#define NUM2STR_DECIMALWIDTH 10
FString::FString():m_pStr(NULL),m_uFlag(0)
{

}

FString::FString( const FString& srcfstr ):m_pStr(NULL),m_uFlag(0)
{
	CHECKVALID( srcfstr.m_pStr );
	Utils::setBit( m_uFlag, BIT_NEWED, true );
	bool iswstr = Utils::getBit( m_uFlag, BIT_STRTYPE );
	Utils::setBit( m_uFlag, BIT_STRTYPE, iswstr );
	if ( iswstr )
	{
		int len = wcslen((TCHAR*)srcfstr.m_pStr);
		int bytecount = sizeof(TCHAR)*(len+1);
		TCHAR* str = new TCHAR[len+1];
		memcpy_s( (void*)str, bytecount, srcfstr.m_pStr, bytecount );
		m_pStr = (void*)str;
	}
	else
	{
		int len = strlen( (CHAR*)srcfstr.m_pStr );
		int bytecount = sizeof(CHAR)*(len+1);
		CHAR* str = new CHAR[len+1];
		memcpy_s( (void*)str, bytecount, srcfstr.m_pStr, bytecount );
		m_pStr = (void*)str;
	}
}

FString::FString( LPCSTR p ):m_uFlag(0)
{
	m_pStr = (void *)p;
}

FString::~FString()
{
	CHECKVALID( m_pStr );
	bool newed = Utils::getBit(m_uFlag,BIT_NEWED);
	CHECKVALID( newed );
	bool isWStr = Utils::getBit( m_uFlag, BIT_STRTYPE );
	CONDITIONEXE( isWStr, delete[] (WCHAR*)m_pStr, delete[] (CHAR*)m_pStr );
}

string FString::toStdString()
{
	bool isStr = !Utils::getBit( m_uFlag, BIT_STRTYPE );
	IF( isStr )
		return string((CHAR*)m_pStr);
	ELSE
		return "";
	ENDIF
}

wstring FString::toStdWString()
{
	CHECKVALIDRETURN( m_pStr, L"");
	bool isWStr = Utils::getBit( m_uFlag, BIT_STRTYPE );
	CHECKVALIDRETURN( !isWStr, (LPWSTR)m_pStr );
	LPWSTR wp = NULL;
	int len = MultiByteToWideChar(CP_ACP,0,(LPCSTR)m_pStr,-1,wp,0);
	IF( len > 0 )
		wp = new WCHAR[len];
		uint32_t l = len;
		CHECKVALIDRETURN( l <= 0x3fffffff, L"");
		Utils::setBit( m_uFlag, BIT_NEWED , true);
		Utils::setBit( m_uFlag, 0, BIT_NEWED, l );
		MultiByteToWideChar(CP_ACP,0,(LPCSTR)m_pStr,-1,wp,len);
		return wp;
	ELSEIF( !len )		
		switch( GetLastError() )
		{
			case ERROR_INSUFFICIENT_BUFFER:
				m_sErr = "buffer size not enough";
				break;
			case ERROR_INVALID_FLAGS:
				m_sErr = "dwFlags not invalid";
				break;
			case ERROR_INVALID_PARAMETER:
				m_sErr = "any parameter invalid";
				break;
			case ERROR_NO_UNICODE_TRANSLATION:
				m_sErr = "invalid unicode character in src str";
				break;
		}
	ENDIF
	return L"";
}

string FString::getLastErrorStr()
{
	return m_sErr;
}

FString FString::number( int num)
{
	int len = numLen(num);
	PSTR  c = new CHAR[len+1];
	sprintf_s( c, len+1, "%d", num);
	return FString(c);
}

FString FString::number( double num )
{
	int len = intlen( num );
	CHECKVALIDRETURN( len >= 1 , FString() );
	int buflen = len + NUM2STR_DECIMALWIDTH + 2;
	int formatstrlen = 2/*%d*/ + numLen(len) + 1/*.*/ + NUM2STR_DECIMALWIDTH + 2/* "lf" */ + 1/*'\0'*/;
	CHAR formatstr[ 1 + 10/*numLen(len)*/ + 1 + NUM2STR_DECIMALWIDTH + 2 + 1 ], buf[ 20/*len*/ + NUM2STR_DECIMALWIDTH + 1 ];
	sprintf_s( formatstr, formatstrlen , "%%%d.%dlf", len + NUM2STR_DECIMALWIDTH, NUM2STR_DECIMALWIDTH );
	sprintf_s( buf, buflen, formatstr, num );
	FString ret = FString( buf );
	return ret;
}

int FString::numLen( int num)
{
	CHECKVALIDRETURN( num , 1 );
	int num_abs = abs(num);
	int len = int(log10(double(num_abs)));
	return len + (num_abs>=pow(double(10),double(len))) + ( num_abs != num );
}

int FString::numLen( int64_t num )
{
	CHECKVALIDRETURN( num , 1 );
	int64_t num_abs = ( num > 0 ? num : -num );
	int len = int(log10(double(num_abs)));
	return len + (num_abs>=pow(double(10),double(len))) + ( num_abs != num );
}

int FString::intlen( double num )
{
	CHECKVALIDRETURN( num , 1 );
	int64_t intpart = int64_t(num);
	return numLen( intpart );
}
