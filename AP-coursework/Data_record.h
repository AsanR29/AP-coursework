#pragma once
#include "Device.h"
class Data_record
{
private:
	
protected:
	Device* owner;
	virtual std::string getDataString() = 0;
public:
	Data_record();
	Data_record(Device*);
	void PrintLine();
};

