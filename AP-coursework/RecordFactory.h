#pragma once
//I want to call it a record shop so bad...

#include "Device.h"

#include <map>
#include <chrono>

#include <format>
#include <fstream>
class RecordFactory
{
private:
	class Data_record
	{
	private:
		std::string devicename;
		char unit;
		std::string data;
		std::chrono::time_point<std::chrono::system_clock> record_time;
	public:
		//Data_record();
		Data_record(std::string name, char unit, std::string data);
		std::string toFile();
	};

	static std::map<std::pair<std::string, char>, Data_record*> record_map;
public:
	static void makeRecord(std::string name, char unit, std::string data);
	//static Data_record* makeRecord(std::string, Device*, float);
	static void clear();
	static void dumpRecords();
};