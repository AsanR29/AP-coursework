#include "Trigger.h"

void setOff(Device* device)
{
	device->Off();
}
void setOn(Device* device)
{
	device->On();
}
std::map<action_type, int> const Trigger::action_to_int = std::map<action_type, int>
{
	{&setOff, 0},
	{&setOn, 1},
};
int Trigger::toInt()
{
	return action_to_int.at(action);
}

Trigger::Trigger(Device* device, int type, std::chrono::time_point<std::chrono::system_clock> time)
{
	setoff_time = time;
	target = device;
	switch (type)
	{
	case 0:
		action = &setOff; break;
	case 1:
		action = &setOn; break;
	default:
		action = nullptr;
	}
}

void Trigger::Use() const
{
	action(target);
}
std::chrono::time_point<std::chrono::system_clock> Trigger::GetTime() const
{
	return setoff_time;
}
void Trigger::ResetTime(std::chrono::time_point<std::chrono::system_clock> time)
{
	setoff_time = time; return;
}

bool Trigger::operator<(const Trigger b) const
{
	if (setoff_time < b.setoff_time) { return true; }
	return false;
}

void Trigger::PrintLine() const
{
	//std::cout << setoff_time << ": ";
	switch (action_to_int.at(action))
	{
	case 0: std::cout << "Turn off"; break;
	case 1: std::cout << "Turn on"; break;
	}
	return;
}