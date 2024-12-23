#pragma once
#include "Data_record.h"
class C_record : public Data_record
{
private:
	float _temperature;
	std::string Data_record::getDataString();
protected:
public:
	C_record(Device*, float);
	C_record(C_record*);
	void updateTemperature(float);
};

