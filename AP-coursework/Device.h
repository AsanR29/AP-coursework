#pragma once
#include <iostream>
#include <string>
class Device
{
private:
protected:
	std::string _name;
public:
	Device();
	Device(std::string);
	std::string getName();
};

