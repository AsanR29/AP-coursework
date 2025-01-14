#pragma once
#include "Device.h"
#include "Schedule.h"

class Light : public Device
{
private:
	//data members
	int brightness;
	Schedule schedule;

	//private input functions
	void TakeBrightness();
public:
	//constructors
	Light(std::string name);

	//getter
	int getBrightness();

	//setter
	void updateBrightness(int);

	//used by CL_Menu to access private functions
	int TakeInput(int input);
	
	//used for command line output
	void PrintLine();
	std::string tagline();

	//public methods primarily for file input/output
	Schedule* GetSchedule();
	friend std::ofstream& operator<<(std::ofstream& ost, Light& device);
	friend std::ifstream& operator>>(std::ifstream& ist, Light& device);

	//destructor
	~Light();
};

