#include "Sensor.h"

Sensor::Sensor(std::string a)
{
	_name = a;
	live_temperature = new C_record(this, 0.0f);
	live_humidity = new H_record(this, 0);
	return;
}

void Sensor::PrintLine()
{
	std::cout << "Sensor: " << getName() << "\n";
	std::cout << "Temperature "; live_temperature->PrintLine(); std::cout << "C\n";
	std::cout << "Humidity "; live_humidity->PrintLine(); std::cout << "%\n";
	return;
}

C_record Sensor::updateTemperature(float a)
{
	C_record* b = new C_record(live_temperature);
	live_temperature->updateTemperature(a);
	return b;
}

H_record Sensor::updateHumidity(int a)
{
	H_record* b = new H_record(live_humidity);
	live_humidity->updateHumidity(a);
	return b;
}