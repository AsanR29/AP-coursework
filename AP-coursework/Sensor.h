#pragma once
#include "Device.h"
#include "RecordFactory.h"

class Sensor : public Device
{
private:
	double live_temperature;
	int live_humidity;

	void TakeTemperature();
	void TakeHumidity();
public:
	Sensor(std::string name);
	void PrintLine();
	std::string tagline();

	int TakeInput(int input);

	void updateTemperature(double);
	void updateHumidity(int);
	
};

