#include "RecordFactory.h"
std::map<std::pair<std::string, char>, RecordFactory::Data_record*> RecordFactory::record_map;
std::ofstream RecordFactory::record_collection = std::ofstream{ "Present_day.txt", std::ios_base::app };

RecordFactory::Data_record::Data_record(std::string name, char unit, std::string data) : devicename(name), unit(unit), data(data)
{
	record_time = std::chrono::system_clock::now();
	//std::ofstream present_day;
	//present_day.open("Present_day.txt", std::ios_base::app);
	//record_collection = &present_day;
};
RecordFactory::Data_record::Data_record(std::string name, char unit, std::string data, std::time_t timestamp) : devicename(name), unit(unit), data(data)
{
	record_time = std::chrono::system_clock::from_time_t(timestamp);
}

std::string RecordFactory::Data_record::toString()
{
	return (devicename + " , " + unit + ' ' + data + ' ');
}
std::time_t RecordFactory::Data_record::toTime_t()
{
	return std::chrono::system_clock::to_time_t(record_time);
}

void RecordFactory::makeRecord(std::string name, char unit, std::string data) //RecordFactory::Data_record*
{
	Data_record* record = new Data_record(name, unit, data);
	std::pair<std::string, char> key(name, unit);
	if (record_map.count(key) > 0)
	{
		record_collection << (*record_map[key]);
	}
	record_map[key] = record;
	return;
	//return nullptr;
	//return new Data_record(name,unit,data);
}

void RecordFactory::clear()
{
	std::map<std::pair<std::string, char>, RecordFactory::Data_record*>::iterator record_it;
	RecordFactory::Data_record* record_p;
	for (record_it = record_map.begin(); record_it != record_map.end(); record_it++)
	{
		record_p = (*record_it).second;
		delete record_p;
	}
	record_map.clear();
	return;
}

void RecordFactory::dumpRecords()
{
	std::map<std::pair<std::string, char>, RecordFactory::Data_record*>::const_iterator record_it;
	RecordFactory::Data_record* record_p;

	std::chrono::time_point timestamp = std::chrono::system_clock::now();
	std::time_t dump_time = std::chrono::system_clock::to_time_t(timestamp);
	//std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> const hms {std::chrono::floor<std::chrono::seconds>(timestamp) };
	//std::string file_name = std::format("{:%F-%H-%M-%S}.txt",hms);

	//std::string file_name = "Dump.txt";
	//std::ofstream ost{ file_name };

	//ost.open(file_name);

	//std::string write_text = "";

	for (record_it = record_map.begin(); record_it != record_map.end(); record_it++)
	{
		record_p = (*record_it).second;
		//write_text += record_p->toFile();
		record_collection << (*record_p);//record_p->toString() << record_p->toTime_t() << "\n";
		record_collection << record_p->toString() << dump_time << "\n";
	}

	//ost << write_text;
	record_collection.close();
	return;
}

std::ofstream& operator<<(std::ofstream& ost, RecordFactory::Data_record& record)
{
	//std::cout << record.toFile();
	RecordFactory::Data_record r = record;
	ost << record.toString() << record.toTime_t() << "\n";
	return ost;
}
std::ifstream& operator>>(std::ifstream& ist, RecordFactory::Data_record& record)
{
	std::string devicename;
	char unit;
	std::string data;
	std::time_t timestamp;

	std::string inp{ "" };
	bool space = false;
	while (ist >> inp)
	{
		if (space) { devicename += " "; }
		if (inp != ",") { devicename += inp; }
		space = true;
	}
	ist >> unit >> data >> timestamp;
	record = RecordFactory::Data_record(devicename, unit, data, timestamp);
	return ist;
}