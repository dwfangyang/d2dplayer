#include "SystemServiceCenter.h"
#include "utils.h"

static SystemServiceCenter* syssrvcenter = NULL;
SystemServiceCenter::SystemServiceCenter()
{

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

int SystemServiceCenter::getSysProperty(uint32_t index)
{
	if ( m_mSysInfo.find(index) != m_mSysInfo.end() )
	{
		return m_mSysInfo[index];
	}
	return 0;
}

void SystemServiceCenter::destroyInstance()
{
	SAFEDELETE(syssrvcenter);
}