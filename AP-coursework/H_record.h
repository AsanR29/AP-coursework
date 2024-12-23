#pragma once
#include "Data_record.h"
class H_record : public Data_record
{
private:
	int _humidity;
	std::string Data_record::getDataString();
protected:
public:
	H_record(Device*, int);
	H_record(H_record*);
	void updateHumidity(int);
};

