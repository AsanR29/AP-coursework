#include "Device.h"

Device::Device() {};
Device::Device(std::string a) : _name(a) {};

std::string Device::getName()
{
	return _name;
}