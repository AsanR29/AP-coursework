#include "RecordFactory.h"
std::map<std::pair<std::string, char>, RecordFactory::Data_record*> RecordFactory::record_map;

RecordFactory::Data_record::Data_record(std::string name, char unit, std::string data) : devicename(name), unit(unit), data(data) {};

std::string RecordFactory::Data_record::toFile()
{
	//return (devicename + " , " + unit + ' ' + data + ' '); std::cout << &record_time; +"\n");
	return (devicename + " , " + unit + ' ' + data + ' ' + "timestamp" +"\n");
}

void RecordFactory::makeRecord(std::string name, char unit, std::string data) //RecordFactory::Data_record*
{
	Data_record* record = new Data_record(name, unit, data);
	std::pair<std::string, char> key(name, unit);
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
	std::cout << "one" << "\n";
	std::map<std::pair<std::string, char>, RecordFactory::Data_record*>::iterator record_it;
	RecordFactory::Data_record* record_p;

	std::chrono::time_point timestamp = std::chrono::system_clock::now();
	//std::chrono::year_month_day ymd { std::chrono::floor<std::chrono::days>(timestamp) };
	std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> const hms {std::chrono::floor<std::chrono::seconds>(timestamp) };
	//std::string file_name = std::format("{:%F}", ymd);//("{%F-%h-%m-%s}", std::chrono::floor<std::chrono::seconds>(timestamp) );
	std::string file_name = std::format("{:%F-%H-%M-%S}.txt",hms);
	std::ofstream ost{ file_name };
	//ost.open(file_name);

	std::string write_text = "";

	for (record_it = record_map.begin(); record_it != record_map.end(); record_it++)
	{
		record_p = (*record_it).second;
		write_text += record_p->toFile();
	}
	std::cout << file_name << "\n";
	std::cout << write_text << "\n";
	ost << write_text;
	ost.close();
	std::cout << "two" << "\n";
	return;
}