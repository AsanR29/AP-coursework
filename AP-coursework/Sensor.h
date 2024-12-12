#pragma once
#include "Device.h"
#include "T_record.h"
class Sensor : public Device
{
private:
	T_record* live_data;
public:
	Sensor(std::string);
	void PrintLine();
	T_record updateData(float);
};

