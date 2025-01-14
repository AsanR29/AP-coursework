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
	void TakeSleepTimer(T* device)
	{
		std::chrono::minutes start;
		std::chrono::minutes end;
		int hour, minute;
		std::string error_msg = "Please enter the time of day in a 24-hour format, like 23:59\n";

		std::cout << "Enter when the Socket should begin sleeping from, in[23:59] format\n";
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
	void TakeOneTrigger(T* device)
	{
		int type = -1;
		std::cout << "Which action should be scheduled\n0: Turn off\n1: Turn on\n";
		input_int_inrange(type, 1);

		std::chrono::minutes start;
		int hour, minute;
		std::string error_msg = "Please enter the time of day in a 24-hour format, like 23:59\n";

		std::cout << "Enter when the Socket should begin sleeping from, in[23:59] format\n";
		input_timeofday(hour, minute, error_msg);
		start = std::chrono::minutes(hour * 60) + std::chrono::minutes(minute);

		addTrigger(device, type, start);
		return;
	}
	bool isEmpty();

	int TakeInput(Device* device, int input, int type);
	void printSchedule();

	void DeleteTriggers();
	friend std::ofstream& operator<<(std::ofstream& ost, Schedule& schedule);
};
