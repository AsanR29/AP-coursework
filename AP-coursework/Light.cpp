#include "Light.h"


//constructors
Light::Light(std::string name) : Device(name)
{
	brightness = 0;
	schedule = Schedule();
}

//used by CL_Menu to access private functions
int Light::TakeInput(int input)
{
	switch (input)
	{
	case 0:
		TakeBrightness();
		break;
	case 1:
		//returning 3 tells CL_Menu to Light's schedule's menu
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
void Light::updateBrightness(int a)
{
	brightness = a; return;
}

void Light::TakeBrightness()
{
	int new_brightness;
	std::string error_message = "Invalid percentage.\n";
	input_number(new_brightness, error_message);

	updateBrightness(new_brightness);
	return;
}

//getter
int Light::getBrightness()
{
	if (status) { return brightness; }
	return 0;	//0 effective brightness when its turned off
}

//used for command line output
std::string Light::tagline()
{
	return "Light: " + _name;
}
void Light::PrintLine()
{
	std::cout << tagline() << " " << tellStatus() << "\nBrightness at " << getBrightness() << "%\n";
}

//public methods primarily for file input/output
Schedule* Light::GetSchedule()
{
	return &schedule;
}
std::ofstream& operator<<(std::ofstream& ost, Light& device)
{
	ost << device._name << " , " << (device.status ? 1 : 0) << " " << device.brightness << "\n";
	return ost;
}
std::ifstream& operator>>(std::ifstream& ist, Light& device)
{
	ist >> device.status >> device.brightness;
	return ist;
}

//destructor
Light::~Light()
{
	schedule.DeleteTriggers();
}