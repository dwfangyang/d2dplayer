#include "SystemServiceCenter.h"
#include "utils.h"

static SystemServiceCenter* syssrvcenter = NULL;
SystemServiceCenter::SystemServiceCenter()
{
	m_mSysInfo[Utils::SCREEN_WIDTH] = GetSystemMetrics(SM_CXSCREEN);
	m_mSysInfo[Utils::SCREEN_HEIGHT] = GetSystemMetrics(SM_CYSCREEN);
}

SystemServiceCenter::~SystemServiceCenter()
{

}

SystemServiceCenter* SystemServiceCenter::getInstance()
{
	if ( !syssrvcenter )
	{
		syssrvcenter = new SystemServiceCenter();		
	}
	return syssrvcenter;
}

int64_t SystemServiceCenter::getSysProperty(uint32_t index)
{
	if ( m_mSysInfo.find(index) != m_mSysInfo.end() )
	{
		return m_mSysInfo[index];
	}
	return -1;
}

void SystemServiceCenter::destroyInstance()
{
	SAFEDELETE(syssrvcenter);
}