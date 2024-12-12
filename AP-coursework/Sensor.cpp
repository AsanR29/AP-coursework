#include "Sensor.h"

Sensor::Sensor(std::string a)
{
	_name = a;
	live_data = new T_record(this, 0.0f);
	return;
}

void Sensor::PrintLine()
{
	std::cout << "Sensor ";
	live_data->PrintLine();
	return;
}

T_record Sensor::updateData(float a)
{
	T_record* b = new T_record(live_data);
	live_data->updateTemperature(a);
	return b;
}