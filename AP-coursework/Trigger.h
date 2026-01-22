#pragma once
#include <chrono>
#include "Device.h"

typedef void (*action_type)(Device*);
class Trigger
{
private:
	std::chrono::time_point<std::chrono::system_clock> setoff_time;
	Device* target;
	action_type action;
public:
	static const std::map<action_type, int> action_to_int;
	int toInt();

	void Use() const;
	std::chrono::time_point<std::chrono::system_clock> GetTime() const;
	void ResetTime(std::chrono::time_point<std::chrono::system_clock> time);

	Trigger(Device* device, int type, std::chrono::time_point<std::chrono::system_clock> time);
	void PrintLine() const;

	bool operator<(const Trigger b) const;
};

void setOn(Device* device);
void setOff(Device* device);

