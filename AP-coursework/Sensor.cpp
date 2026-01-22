#include "Sensor.h"

//constructors
Sensor::Sensor(std::string name) : Device(name)	//used when creating a new device
{
	live_temperature = 0.0f;
	live_humidity = 0;
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
		//Returning 2 tells CL_Menu to use DeviceFactory::renameDevice
		return 2;
	case 4:
		//Tells CL_Menu to close the menu with this device opened
		return 0;	
	}
	return 1;
}

//setters
//Records are made using the new value so that default values of zero aren't mistaken for collected-data
//If the program were to recieve signals from real devices, they should use these setters directly
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

//private input functions
void Sensor::TakeTemperature()
{
	double new_temp;
	std::string error_message = "Invalid temperature.\n";
	input_number(new_temp, error_message);

	updateTemperature(new_temp);
	return;
}
void Sensor::TakeHumidity()
{
	int new_humidity;
	std::string error_message = "Invalid Humidity.\n";
	input_number(new_humidity, error_message);	//loops input

	updateHumidity(new_humidity);
	return;
}

//command line output
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

//file input/output
std::ofstream& operator<<(std::ofstream& ost, Sensor& device)
{
	ost << device._name << " , " << device.live_temperature << " " << device.live_humidity << "\n";	//the format of a Sensor record
	return ost;
}
std::ifstream& operator>>(std::ifstream& ist, Sensor& device)
{
	ist >> device.live_temperature >> device.live_humidity;
	//DeviceFactory needs the devicename during construction; the _name is read externally before this operator is used
	//Sensor record format is 'devicename , temperature humidity\n'
	return ist;
}