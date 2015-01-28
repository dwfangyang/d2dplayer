#ifndef __MAINAPP_SRC_SYSTEMSERVICECENTER_H
#define __MAINAPP_SRC_SYSTEMSERVICECENTER_H

#include "utils.h"
#include "inttypes.h"
#include <iostream>
#include <map>
using namespace std;

class SystemServiceCenter
{
public:
	static SystemServiceCenter* getInstance();
	static void destroyInstance();
	int64_t		getSysProperty(uint32_t index);
	double		getCurrentCpuUsageValue();
private: 
	SystemServiceCenter();
	~SystemServiceCenter();
	LRESULT WINAPI init();

private:
	std::map<uint32_t,int64_t>				m_mSysInfo;
};

#endif