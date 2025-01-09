#pragma once
#include <chrono>
#include "Device.h"

class Trigger
{
private:
	std::chrono::time_point<std::chrono::system_clock> setoff_time;
	Device* target;
	void (* action)(Device*);
public:
	void Use();
	std::chrono::time_point<std::chrono::system_clock> GetTime() const;

	Trigger(Device* device, int type, std::chrono::time_point<std::chrono::system_clock> time);
	void PrintLine();

	bool operator<(Trigger b);
};

void setOn(Device* device);
void setOff(Device* device);

