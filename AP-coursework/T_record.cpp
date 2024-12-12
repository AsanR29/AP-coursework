#include "T_record.h"

T_record::T_record(Device* a, float b) : _temperature(b)
{
	owner = a;
};
T_record::T_record(T_record* a)
{
	owner = a->owner;
	_temperature = a->_temperature;
}

std::string T_record::getDataString()
{
	return std::to_string(_temperature);
}

void T_record::updateTemperature(float a)
{
	_temperature = a;
}