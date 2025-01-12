#include "Socket.h"

Socket::Socket(std::string name) : Device(name)
{
	live_energy = 0.0f;
	schedule = Schedule();
};
Socket::Socket(std::string name, bool status, double energy) : Device(name, status), live_energy(energy)
{
	schedule = Schedule();
}

Schedule* Socket::GetSchedule()
{
	return &schedule;
}

int Socket::TakeInput(int input)
{
	switch (input)
	{
	case 0:
		TakeEnergy();
		break;
	case 1:
		return 3;
	case 2:
		//TakeDeviceName();
		return 2;
	case 3:
		return 0;
	}
	return 1;
}

void Socket::TakeEnergy()
{
	std::string empty;
	double new_energy;
	bool loop = true;
	while (loop)
	{
		std::cin >> new_energy;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin >> empty;
			std::cout << "Invalid kWh.\n";
		}
		else {
			loop = false;
		}
	}
	updateEnergy(new_energy);
	return;
}

void Socket::updateEnergy(double a)
{
	live_energy = a;
	RecordFactory::makeRecord(_name, 'W', std::to_string(live_energy));
	return;
}

std::string Socket::tagline()
{
	return "Socket: " + _name;
}
void Socket::PrintLine()
{
	std::cout << tagline() << " " << ((status)?" Status:On":"Status:Off") << "\n" << live_energy << "kWh\n";
}
std::ofstream& operator<<(std::ofstream& ost, Socket& device)
{
	ost << device._name << " , " << (device.status ? 1 : 0) << " " << device.live_energy << "\n";
	return ost;
}
std::ifstream& operator>>(std::ifstream& ist, Socket& device)
{
	//std::string devicename = "";
	//bool status;
	//double energy;

	//input_name<std::ifstream>(ist, devicename, ",");
	ist >> device.status >> device.live_energy;
	//device = Socket(devicename, status, energy);
	return ist;
}