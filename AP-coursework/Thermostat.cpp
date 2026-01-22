#include "Thermostat.h"

//constructors
Thermostat::Thermostat(std::string name) : Device(name)
{
	schedule = Schedule();
}

//used by CL_Menu to access private functions
int Thermostat::TakeInput(int input)
{
	std::chrono::time_point<std::chrono::system_clock> one_hour_later;
	switch (input)
	{
	case 0:
		//Heating boost
		status = true;
		one_hour_later = std::chrono::system_clock::now() + std::chrono::minutes(60);
		std::chrono::minutes minutes = duration_cast<std::chrono::minutes>(one_hour_later- TriggerFactory::getPresentDay());
		TriggerFactory::makeTrigger(this, 0, minutes); //turns it off in an hour
		//bypassing schedule's addTrigger so that its not added to the schedule!
		break;
	case 1:
		//returning 3 tells CL_Menu to open Thermostat's schedule's menu
		return 3;
	case 2:
		//Returning 2 tells CL_Menu to use DeviceFactory::renameDevice
		return 2;
	case 4:
		//Tells CL_Menu to close the menu with this device opened
		return 0;
	}
	return 1;
}

//used for command line output
std::string Thermostat::tagline()
{
	return "Thermostat: " + _name;
}
void Thermostat::PrintLine()
{
	std::cout << tagline() << " " << tellStatus() << "\n";
}

//public methods primarily for file input/output
Schedule* Thermostat::GetSchedule()
{
	return &schedule;
}
std::ofstream& operator<<(std::ofstream& ost, Thermostat& device)
{
	ost << device._name << " , " << (device.status ? 1 : 0) << "\n";
	return ost;
}
std::ifstream& operator>>(std::ifstream& ist, Thermostat& device)
{
	ist >> device.status;
	return ist;
}

//destructor
Thermostat::~Thermostat()
{
	schedule.DeleteTriggers();
}