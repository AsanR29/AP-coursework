#include "Radiator.h"

//constructors
Radiator::Radiator(std::string name) : Device(name)
{
	current_temperature = 0;
	schedule = Schedule();
}

//used by CL_Menu to access private functions
int Radiator::TakeInput(int input)
{
	switch (input)
	{
	case 0:
		TakeTemperature();
		break;
	case 1:
		//returning 3 tells CL_Menu to Radiator's schedule's menu
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

//setter
void Radiator::updateTemperature(int a)
{
	current_temperature = a; return;
}

void Radiator::TakeTemperature()
{
	int new_temperature;
	std::string error_message = "Invalid percentage.\n";
	input_number(new_temperature, error_message);

	updateTemperature(new_temperature);
	return;
}

//used for command line output
std::string Radiator::tagline()
{
	return "Radiator: " + _name;
}
void Radiator::PrintLine()
{
	std::cout << tagline() << " " << tellStatus() << "\nCurrent temperature at " << current_temperature << "C\n";
}

//public methods primarily for file input/output
Schedule* Radiator::GetSchedule()
{
	return &schedule;
}
std::ofstream& operator<<(std::ofstream& ost, Radiator& device)
{
	ost << device._name << " , " << (device.status ? 1 : 0) << " " << device.current_temperature << "\n";
	return ost;
}
std::ifstream& operator>>(std::ifstream& ist, Radiator& device)
{
	ist >> device.status >> device.current_temperature;
	return ist;
}

//destructor
Radiator::~Radiator()
{
	schedule.DeleteTriggers();
}