#pragma once
#include "Device.h"
#include "RecordFactory.h"

class Sensor : public Device
{
private:
	//data members
	double live_temperature;
	int live_humidity;

	//private input functions
	void TakeTemperature();
	void TakeHumidity();
public:
	//constructors
	Sensor(std::string name);

	//setters which create Data_records
	void updateTemperature(double);
	void updateHumidity(int);

	//used by CL_Menu to call private methods
	int TakeInput(int input);

	//command line output
	void PrintLine();
	std::string tagline();
	
	//used for file input/output
	friend std::ofstream& operator<<(std::ofstream& ost, Sensor& device);
	friend std::ifstream& operator>>(std::ifstream& ist, Sensor& device);
};

