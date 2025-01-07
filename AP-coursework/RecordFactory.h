#pragma once
//I want to call it a record shop so bad...

#include "Device.h"

#include <map>
#include <chrono>
#include <time.h>

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
		Data_record(std::string name, char init, std::string data, std::time_t timestamp);
		std::string toString();
		std::time_t toTime_t();
	};

	static std::map<std::pair<std::string, char>, Data_record*> record_map;
	static std::ofstream record_collection;
public:
	static void makeRecord(std::string name, char unit, std::string data);
	//static Data_record* makeRecord(std::string, Device*, float);
	static void clear();
	static void dumpRecords();

	friend std::ofstream& operator<<(std::ofstream& ost, Data_record& record);
	friend std::ifstream& operator>>(std::ifstream& ist, Data_record& record);
};

//std::string timeToString(std::chrono::time_point<std::chrono::system_clock> t);