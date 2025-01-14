#include "TriggerFactory.h"

std::chrono::time_point<std::chrono::system_clock> TriggerFactory::present_day = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
std::chrono::time_point<std::chrono::system_clock> TriggerFactory::last_time = std::chrono::system_clock::now();
std::multiset<Trigger>* TriggerFactory::trigger_set = new std::multiset<Trigger>();

Trigger* TriggerFactory::makeTrigger(Device* device, int type, std::chrono::minutes time)
{
	std::chrono::time_point<std::chrono::system_clock> setoff_time = present_day + time;
	Trigger* trigger_p = new Trigger(device, type, setoff_time);
	trigger_set->insert(*trigger_p);	//storing a copy
	return trigger_p;
}
void TriggerFactory::resetTrigger(Trigger* trigger_p, std::chrono::minutes time)
{
	std::chrono::time_point<std::chrono::system_clock> setoff_time = present_day + time;
	trigger_p->ResetTime(setoff_time);
	trigger_set->insert(*trigger_p);	//storing a copy
	return;
}

void TriggerFactory::fireAll()
{
	std::multiset<Trigger>::const_iterator trigger_it = (*trigger_set).cbegin();
	//Trigger* trigger_p;
	
	for (trigger_it = trigger_set->cbegin(); trigger_it != trigger_set->cend(); ++trigger_it)
	{
		//trigger_p = *trigger_it;
		if (trigger_it->GetTime() > last_time)
		{
			trigger_set->erase(trigger_set->cbegin(), trigger_it);
			return; //
		}
		trigger_it->Use();
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

void TriggerFactory::clear()
{
	delete trigger_set;
}