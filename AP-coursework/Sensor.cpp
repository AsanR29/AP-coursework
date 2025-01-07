#include "Sensor.h"

Sensor::Sensor(std::string name) : Device(name)
{
	live_temperature = 0.0f;
	live_humidity = 0;
	return;
}

std::string Sensor::tagline()
{
	return "Sensor: " + _name;
}
void Sensor::PrintLine()
{
	std::cout << tagline() << "\n";
	std::cout << "Temperature " << live_temperature << "C\n";
	std::cout << "Humidity " << live_humidity << "%\n";
	return;
}

int Sensor::TakeInput(int input)
{
	switch (input)
	{
		case 0:
			TakeTemperature();
			break;
		case 1:
			TakeHumidity();
			break;
		case 2:
			//TakeDeviceName();
			return 2;
		case 3:
			return 0;
	}
	return 1;
}

void Sensor::TakeTemperature()
{
	std::string empty;
	double new_temp;
	bool loop = true;
	while (loop)
	{
		std::cin >> new_temp;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin >> empty;
			std::cout << "Invalid temperature.\n";
		}
		else {
			loop = false;
		}
	}
	updateTemperature(new_temp);
	return;
}
void Sensor::TakeHumidity()
{
	std::string empty;
	int new_humidity;
	bool loop = true;
	while (loop)
	{
		std::cin >> new_humidity;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin >> empty;
			std::cout << "Invalid Humidity.\n";
		}
		else {
			loop = false;
		}
	}
	updateHumidity(new_humidity);
	return;
}

void Sensor::updateTemperature(double a)
{
	live_temperature = a;
	RecordFactory::makeRecord(_name, 'C', std::to_string(live_temperature));
	return;
}

void Sensor::updateHumidity(int a)
{
	live_humidity = a;
	RecordFactory::makeRecord(_name, '%', std::to_string(live_humidity));
	return;
}