#include "Socket.h"

//constructors
Socket::Socket(std::string name) : Device(name)
{
	live_energy = 0.0f;
	schedule = Schedule();
};

int Socket::TakeInput(int input)
{
	switch (input)
	{
	case 0:
		TakeEnergy();
		break;
	case 1:
		//returning 3 tells CL_Menu to Socket's schedule's menu
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

//setters
void Socket::updateEnergy(double a)
{
	live_energy = a;
	RecordFactory::makeRecord(_name, 'W', std::to_string(live_energy));
	return;
}

//private input function
void Socket::TakeEnergy()
{
	double new_energy;
	std::string error_message = "Invalid kWh.\n";
	input_number(new_energy, error_message);

	updateEnergy(new_energy);
	return;
}

//command line output
std::string Socket::tagline()
{
	return "Socket: " + _name;
}
void Socket::PrintLine()
{
	std::cout << tagline() << " " << tellStatus() << "\n" << live_energy << "kWh\n";
}

//Getter for when the program needs to use the schedule
Schedule* Socket::GetSchedule()
{
	return &schedule;
}
//for file input/output
std::ofstream& operator<<(std::ofstream& ost, Socket& device)
{
	ost << device._name << " , " << (device.status ? 1 : 0) << " " << device.live_energy << "\n";
	return ost;
}
std::ifstream& operator>>(std::ifstream& ist, Socket& device)
{
	ist >> device.status >> device.live_energy;
	return ist;
}

//destructor
Socket::~Socket()
{
	schedule.DeleteTriggers();
}