#include "Device.h"

Device::Device() {};
Device::Device(std::string a) : _name(a), status(false) {};

std::string Device::getName()
{
	return _name;
}

void Device::updateDeviceName(std::string name)
{
	_name = name;
	return;
}

void Device::TakeDeviceName()
{
	std::string new_name;
	bool loop = true;
	while (loop)
	{
		std::cin >> new_name;
		if (new_name.find('|'))
		{
			std::cout << "Invalid device name.\n";
		}
		else {
			loop = false;
		}
	}
	updateDeviceName(new_name);
	return;
}