#include "W_record.h"

W_record::W_record(Device* a, int b) : _watts(b)
{
	owner = a;
};
W_record::W_record(W_record* a)
{
	owner = a->owner;
	_watts = a->_watts;
}

std::string W_record::getDataString()
{
	return std::to_string(_watts);
}

void W_record::updateWatts(int a)
{
	_watts = a;
}