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
	Sensor();
	Sensor(std::string name);
	Sensor(std::string name, double temperature, int humidity);
	void PrintLine();
	std::string tagline();

	int TakeInput(int input);

	void updateTemperature(double);
	void updateHumidity(int);
	
	friend std::ofstream& operator<<(std::ofstream& ost, Sensor& device);
	friend std::ifstream& operator>>(std::ifstream& ist, Sensor& device);
};

