#pragma once
#include "Data_record.h"
class T_record : public Data_record
{
private:
	float _temperature;
protected:
	std::string Data_record::getDataString();
public:
	T_record(Device*, float);
	T_record(T_record*);
	void updateTemperature(float);
};

