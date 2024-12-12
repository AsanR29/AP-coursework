#include "Data_record.h"

Data_record::Data_record() :owner(nullptr){};
Data_record::Data_record(Device* a) : owner(a) {};

void Data_record::PrintLine()
{
	std::string name = (*owner).getName();
	std::string data = getDataString();
	std::cout << name << " : " << data << "\n";
	return;
}