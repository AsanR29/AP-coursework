#include "C_record.h"

C_record::C_record(Device* a, float b) : _temperature(b)
{
	owner = a;
};
C_record::C_record(C_record* a)
{
	owner = a->owner;
	_temperature = a->_temperature;
}

std::string C_record::getDataString()
{
	return std::to_string(_temperature);
}

void C_record::updateTemperature(float a)
{
	_temperature = a;
}