#include "FString.h"
#include "utils.h"

FString::FString():m_pStr(NULL),m_uFlag(0)
{

}

FString::FString( LPCSTR p ):m_uFlag(0)
{
	m_pStr = (void *)p;
	Utils::setBit(m_uFlag,BIT_STRTYPE,false);
}

FString::~FString()
{
	CHECKVALID( m_pStr );
	bool newed = Utils::getBit(m_uFlag,BIT_NEWED);
	IF ( newed )	
		bool isWStr = Utils::getBit( m_uFlag, BIT_STRTYPE );
		IF( isWStr )  
			delete[] (WCHAR*)m_pStr;
		ELSE
			delete[] (CHAR*)m_pStr;
		ENDIF
	ENDIF		
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
	bool isWStr = Utils::getBit( m_uFlag, BIT_STRTYPE );
	IF ( !isWStr )
		LPWSTR wp = NULL;
		int len = MultiByteToWideChar(CP_ACP,0,(LPCSTR)m_pStr,-1,wp,0);
		IF( len > 0 )
			wp = new WCHAR[len];
			uint32_t l = len;
			IF( l > ( 0xffffffff << 2 >> 2) )		THEN( return L"" );
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
	ELSE
		
	ENDIF
	return L"";
}

string FString::getLastErrorStr()
{
	return m_sErr;
}