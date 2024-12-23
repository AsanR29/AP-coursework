#include "RecordFactory.h"

Data_record* RecordFactory::makeRecord(std::string a, Device* b, float c)
{
	if (a == "C_record") {
		return new C_record(b, c);
	}
	return nullptr;
}

Data_record* RecordFactory::makeRecord(std::string a, Device* b, int c)
{
	if (a == "W_record") {
		return new W_record(b, c);
	}
	else if (a == "H_record") {
		return new H_record(b, c);
	}
	return nullptr;
}