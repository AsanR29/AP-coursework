#include "TriggerFactory.h"
std::chrono::time_point<std::chrono::system_clock> TriggerFactory::present_day = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
std::chrono::time_point<std::chrono::system_clock> TriggerFactory::last_time = std::chrono::system_clock::now();
std::multiset<Trigger*> TriggerFactory::trigger_set = std::multiset<Trigger*>();

Trigger* TriggerFactory::makeTrigger(Device* device, int type, std::chrono::minutes time)
{
	std::chrono::time_point<std::chrono::system_clock> setoff_time = present_day + time;
	Trigger* trigger_p = new Trigger(device, type, setoff_time);
	trigger_set.insert(trigger_p);
	return trigger_p;
}
void TriggerFactory::resetTrigger(Trigger* trigger_p, std::chrono::minutes time)
{
	std::chrono::time_point<std::chrono::system_clock> setoff_time = present_day + time;
	trigger_p->ResetTime(setoff_time);
	trigger_set.insert(trigger_p);
	return;
}

void TriggerFactory::fireAll()
{
	std::multiset<Trigger*>::iterator trigger_it = trigger_set.begin();
	Trigger* trigger_p;
	for (trigger_it = trigger_set.begin(); trigger_it != trigger_set.end(); ++trigger_it)
	{
		trigger_p = *trigger_it;
		if (trigger_p->GetTime() > last_time)
		{
			trigger_set.erase(trigger_set.begin(), trigger_it);
			return; //don't delete Triggers from heap here
		}
		trigger_p->Use();
	}
	return;
}

std::chrono::time_point<std::chrono::system_clock> TriggerFactory::getPresentDay() { return present_day; }
void TriggerFactory::setPresentDay(std::chrono::time_point<std::chrono::system_clock> time) { present_day = time; }
//std::chrono::time_point<std::chrono::system_clock> TriggerFactory::getLastTime() { return last_time; }
void TriggerFactory::updateTime(std::chrono::time_point<std::chrono::system_clock> time)
{
	last_time = time;
	fireAll();
	return;
}