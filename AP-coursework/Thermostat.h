#pragma once
#include "Device.h"
#include "Schedule.h"

class Thermostat : public Device
{
private:
	//data members
	Schedule schedule;

	//private input functions
public:
	//constructors
	Thermostat(std::string name);

	//used by CL_Menu to access private functions
	int TakeInput(int input);

	//used for command line output
	void PrintLine();
	std::string tagline();

	//public methods primarily for file input/output
	Schedule* GetSchedule();
	friend std::ofstream& operator<<(std::ofstream& ost, Thermostat& device);
	friend std::ifstream& operator>>(std::ifstream& ist, Thermostat& device);

	//destructor
	~Thermostat();
};

