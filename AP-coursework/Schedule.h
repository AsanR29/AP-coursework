#pragma once
#include "TriggerFactory.h"

class Schedule
{
private:
	std::map<std::chrono::minutes, Trigger*> trigger_set;
public:
	Schedule();
	void addTrigger(Device* device, int type, std::chrono::minutes time);
	void setTriggers();

	template <typename T>
	void TakeSleepTimer(T*);
	template <typename T>
	void TakeOneTrigger(T*);
	bool isEmpty();

	int TakeInput(Device* device, int input, int type);
	void printSchedule();

	friend std::ofstream& operator<<(std::ofstream& ost, Schedule& schedule);
};
