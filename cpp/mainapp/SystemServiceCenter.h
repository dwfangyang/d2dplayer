#include "Windows.h"
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
private: 
	SystemServiceCenter();
	~SystemServiceCenter();

private:
	std::map<uint32_t,int64_t>				m_mSysInfo;
};