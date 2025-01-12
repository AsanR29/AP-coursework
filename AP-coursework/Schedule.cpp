#include "Schedule.h"

Schedule::Schedule()
{
	trigger_set = std::map<std::chrono::minutes, Trigger*>();
}

int Schedule::TakeInput(Device* device, int input, int type)
{
	switch (input)
	{
	case 0:
		printSchedule();
		break;
	case 1:
		switch (type)
		{
		case 0:
			TakeSleepTimer(device);
			break;
		case 1:
			TakeOneTrigger(device);
			break;
		}
		break;
	case 2:
		//delete triggers
		break;
	case 3:
		return 0;
	}
	return 1;
}

void Schedule::addTrigger(Device* device, int type, std::chrono::minutes time)
{
	Trigger* t = TriggerFactory::makeTrigger(device, type, time);
	trigger_set[time] = t;
}
void Schedule::setTriggers()
{
	std::map<std::chrono::minutes, Trigger*>::iterator trigger_it;

	std::chrono::minutes time;
	Trigger* trigger_p;

	for (trigger_it = trigger_set.begin(); trigger_it != trigger_set.end(); trigger_it++)
	{
		time = (*trigger_it).first;
		trigger_p = (*trigger_it).second;
		TriggerFactory::resetTrigger(trigger_p, time);
	}
	return;
}
bool Schedule::isEmpty()
{
	return trigger_set.empty();
}

template <typename T>
void Schedule::TakeSleepTimer(T* device)
{
	std::chrono::minutes start;
	std::chrono::minutes end;
	int hour, minute;
	std::string error_msg = "Please enter the time of day in a 24-hour format, like 23:59\n";
	input_timeofday(hour, minute, error_msg);
	start = std::chrono::minutes(hour * 60) + std::chrono::minutes(minute);

	std::cout << "Enter the time of day that it should turn back on\n";
	input_timeofday(hour, minute, error_msg);
	end = std::chrono::minutes(hour * 60) + std::chrono::minutes(minute);

	//Device* device, int type, std::chrono::minutes time
	addTrigger(device, 0, start);
	addTrigger(device, 1, end);
	return;
}
template <typename T>
void Schedule::TakeOneTrigger(T* device)
{
	int type = -1;
	std::cout << "Which action should be scheduled\n0: Turn off\n1: Turn on\n";
	input_int_inrange(type, 1);

	std::chrono::minutes start;
	int hour, minute;
	std::string error_msg = "Please enter the time of day in a 24-hour format, like 23:59\n";
	input_timeofday(hour, minute, error_msg);
	start = std::chrono::minutes(hour * 60) + std::chrono::minutes(minute);
	
	addTrigger(device, type, start);
	return;
}

void Schedule::printSchedule()
{
	std::map<std::chrono::minutes, Trigger*>::const_iterator trigger_it;

	std::chrono::minutes time;
	Trigger* trigger_p;

	for (trigger_it = trigger_set.cbegin(); trigger_it != trigger_set.cend(); trigger_it++)
	{
		
		time = (*trigger_it).first;
		trigger_p = (*trigger_it).second;
		//std::cout << time << ": ";
		std::cout << std::format("{:%R}", std::chrono::hh_mm_ss(time)) << ", ";
		trigger_p->PrintLine();
		std::cout << "\n";
	}
	return;
}

std::ofstream& operator<<(std::ofstream& ost, Schedule& schedule)
{
	ost << " " << schedule.trigger_set.size() << "\n";
	
	std::map<std::chrono::minutes, Trigger*>::iterator trigger_it;
	Trigger* trigger_p;
	for (trigger_it = schedule.trigger_set.begin(); trigger_it != schedule.trigger_set.end(); trigger_it++)
	{
		trigger_p = (*trigger_it).second;
		ost << trigger_p->toInt() << " " << (*trigger_it).first.count() << "\n";
	}
	return ost;
}