#pragma once
//I want to call it a record shop so bad...
#include "C_record.h"
#include "W_record.h"
#include "T_record.h"
#include "H_record.h"
class RecordFactory
{
public:
	static Data_record* makeRecord(std::string, Device*, int);
	static Data_record* makeRecord(std::string, Device*, float);
};

