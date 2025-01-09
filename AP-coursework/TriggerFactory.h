#pragma once
#include <set>

#include "Trigger.h"

//struct TriggerComp
//{
//	bool operator()(Trigger* a, Trigger* b)
//	{
//		
//	}
//};

class TriggerFactory
{
private:
	static std::chrono::time_point<std::chrono::system_clock> present_day;
	static std::chrono::time_point<std::chrono::system_clock> last_time;
	static std::multiset<Trigger*> trigger_set;
	//int std::multiset<Trigger*>::key_comp();
	static void fireAll();
public:
	static Trigger* makeTrigger(Device* device, int type, std::chrono::minutes time);
	static void resetTrigger(Trigger* trigger_p, std::chrono::minutes time);
	static std::chrono::time_point<std::chrono::system_clock> getPresentDay();
	static void setPresentDay(std::chrono::time_point<std::chrono::system_clock> time);
	//static std::chrono::time_point<std::chrono::system_clock> getLastTime();
	static void updateTime(std::chrono::time_point<std::chrono::system_clock> time);
};

