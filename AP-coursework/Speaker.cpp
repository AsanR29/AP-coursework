#include "Speaker.h"

//constructors
Speaker::Speaker(std::string name) : Device(name)
{
	volume = 0;
}

//used by CL_Menu to access private functions
int Speaker::TakeInput(int input)
{
	switch (input)
	{
	case 0:
		TakeVolume();
		break;
	case 1:
		//Returning 2 tells CL_Menu to use DeviceFactory::renameDevice
		return 2;
	case 3:
		//Tells CL_Menu to close the menu with this device opened
		return 0;
	}
	return 1;
}

//setter
void Speaker::updateVolume(int a)
{
	volume = a; return;
}

void Speaker::TakeVolume()
{
	int new_volume;
	std::string error_message = "Invalid percentage.\n";
	input_number(new_volume, error_message);

	updateVolume(new_volume);
	return;
}

//getter
int Speaker::getVolume()
{
	if (status) { return volume; }
	return 0;	//0 effective volume when its turned off
}

//used for command line output
std::string Speaker::tagline()
{
	return "Speaker: " + _name;
}
void Speaker::PrintLine()
{
	std::cout << tagline() << " " << tellStatus() << "\nVolume at " << getVolume() << "%\n";
}

//public methods for file input/output
std::ofstream& operator<<(std::ofstream& ost, Speaker& device)
{
	ost << device._name << " , " << (device.status ? 1 : 0) << " " << device.volume << "\n";
	return ost;
}
std::ifstream& operator>>(std::ifstream& ist, Speaker& device)
{
	ist >> device.status >> device.volume;
	return ist;
}