#pragma once
#include "Device.h"
class Speaker : public Device
{
private:
	//data members
	int volume;

	//private inout functions
	void TakeVolume();
public:
	//constructors
	Speaker(std::string name);

	//getter
	int getVolume();

	//setter
	void updateVolume(int);

	//used by CL_Menu to access private functions
	int TakeInput(int input);

	//used for command line output
	void PrintLine();
	std::string tagline();

	//public methods primarily for file input/output
	friend std::ofstream& operator<<(std::ofstream& ost, Speaker& device);
	friend std::ifstream& operator>>(std::ifstream& ist, Speaker& device);
};

