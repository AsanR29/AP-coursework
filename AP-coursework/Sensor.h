#pragma once
#include "Device.h"
#include "C_record.h"
#include "H_record.h"
class Sensor : public Device
{
private:
	C_record* live_temperature;
	H_record* live_humidity;
public:
	Sensor(std::string);
	void PrintLine();
	C_record updateTemperature(float);
	H_record updateHumidity(int);
};

