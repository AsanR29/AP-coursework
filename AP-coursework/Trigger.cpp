#include "Trigger.h"

void setOff(Device* device)
{
	device->Off();
}
void setOn(Device* device)
{
	device->On();
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

void Trigger::Use()
{
	action(target);
}
std::chrono::time_point<std::chrono::system_clock> Trigger::GetTime() const
{
	return setoff_time;
}

bool Trigger::operator<(Trigger b)
{
	if (setoff_time < b.setoff_time) { return true; }
	return false;
}

void Trigger::PrintLine()
{
	std::cout << setoff_time << ": ";
	if (action == &setOff) { std::cout << "Turn off"; }
	else { std::cout << "Turn on"; }
	return;
}