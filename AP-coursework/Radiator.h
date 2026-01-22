#pragma once
#include "Device.h"
#include "Schedule.h"

class Radiator : public Device
{
private:
	//data members
	int current_temperature;
	Schedule schedule;

	//private input functions
	void TakeTemperature();
public:
	//constructors
	Radiator(std::string name);

	//setter
	void updateTemperature(int);

	//used by CL_Menu to access private functions
	int TakeInput(int input);

	//used for command line output
	void PrintLine();
	std::string tagline();

	//public methods primarily for file input/output
	Schedule* GetSchedule();
	friend std::ofstream& operator<<(std::ofstream& ost, Radiator& device);
	friend std::ifstream& operator>>(std::ifstream& ist, Radiator& device);

	//destructor
	~Radiator();
};

