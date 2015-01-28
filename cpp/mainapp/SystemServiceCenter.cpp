#include "SystemServiceCenter.h"
#include "Pdh.h"
#include "utils.h"

static PDH_HQUERY cpuQuery;
static PDH_HCOUNTER cpuTotal;
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
		syssrvcenter->init();
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

LRESULT WINAPI SystemServiceCenter::init()
{
	LRESULT ret = S_OK;
	PdhOpenQuery(NULL, NULL, &cpuQuery);
	PdhAddCounter(cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
	PdhCollectQueryData(cpuQuery);
	return ret;
}

double SystemServiceCenter::getCurrentCpuUsageValue()
{
	PDH_FMT_COUNTERVALUE counterVal;

	PdhCollectQueryData(cpuQuery);
	PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
	return counterVal.doubleValue;
}
