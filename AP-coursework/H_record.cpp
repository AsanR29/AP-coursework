#include "H_record.h"

H_record::H_record(Device* a, int b) : _humidity(b)
{
	owner = a;
};
H_record::H_record(H_record* a)
{
	owner = a->owner;
	_humidity = a->_humidity;
}

std::string H_record::getDataString()
{
	return std::to_string(_humidity);
}

void H_record::updateHumidity(int a)
{
	_humidity = a;
}