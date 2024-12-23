#pragma once
#include "Data_record.h"
class W_record : public Data_record
{
private:
	int _watts;
	std::string Data_record::getDataString();
protected:
public:
	W_record(Device*, int);
	W_record(W_record*);
	void updateWatts(int);
};

