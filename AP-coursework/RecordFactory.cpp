#include "RecordFactory.h"
std::map<std::pair<std::string, char>, RecordFactory::Data_record*> RecordFactory::record_map;
std::multiset<RecordFactory::Data_record>* RecordFactory::record_collection = new std::multiset<RecordFactory::Data_record>(); //std::ofstream{ "Present_day.txt", std::ios_base::app };

RecordFactory::Data_record::Data_record() {};
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
std::chrono::time_point<std::chrono::system_clock> RecordFactory::Data_record::toDay()
{
	return std::chrono::floor<std::chrono::days>(record_time);
}

bool RecordFactory::Data_record::operator<(RecordFactory::Data_record record) const
{
	if (record_time < record.record_time) { return true; }
	return false;
}
bool RecordFactory::Data_record::operator<(std::chrono::time_point<std::chrono::system_clock> time)
{
	if (record_time < time) { return true; }
	return false;
}
bool RecordFactory::Data_record::operator>(std::chrono::time_point<std::chrono::system_clock> time)
{
	if (record_time > time) { return true; }
	return false;
}

void RecordFactory::makeRecord(std::string name, char unit, std::string data) //RecordFactory::Data_record*
{
	Data_record* record = new Data_record(name, unit, data);
	std::pair<std::string, char> key(name, unit);
	if (record_map.count(key) > 0)
	{
		RecordFactory::record_collection->insert(*record_map[key]);
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
	delete record_collection;
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
	std::ofstream dump_file = std::ofstream{ "Present_day.txt", std::ios_base::app };

	for (record_it = record_map.cbegin(); record_it != record_map.cend(); record_it++)
	{
		record_p = (*record_it).second;
		//write_text += record_p->toFile();
		dump_file << (*record_p);//record_p->toString() << record_p->toTime_t() << "\n";
		dump_file << record_p->toString() << dump_time << "\n";
	}

	//ost << write_text;
	dump_file.close();
	return;
}

bool RecordFactory::recordDay(std::chrono::time_point<std::chrono::system_clock> day_start, std::chrono::time_point<std::chrono::system_clock> day_end)
{
	bool file_existed = false;
	std::chrono::time_point<std::chrono::system_clock, std::chrono::days> day{ std::chrono::floor<std::chrono::days>(day_start) };
	std::string filename = std::format("{:%F}.txt", day);
	if (std::filesystem::exists(filename))
	{
		loadRecords(filename);
		file_existed = true;
	}
	std::ofstream output_file = std::ofstream{ filename };

	std::set<RecordFactory::Data_record>::iterator first_record = record_collection->end();
	std::set<RecordFactory::Data_record>::iterator record_it;
	RecordFactory::Data_record record_p;

	if (record_collection->size() == 0) { return file_existed; }
	record_it = record_collection->begin();
	record_p = *(record_it);

	for (record_it = record_collection->begin(); record_p < day_start && record_it != record_collection->end(); ++record_it)
	{
		record_p = *record_it;
	}
	if (record_it == record_collection->end()) { return file_existed; }

	first_record = record_it;
	for (record_it = first_record; record_it != record_collection->end(); ++record_it)
	{
		record_p = *record_it;
		output_file << record_p;
		if (record_p > day_end)
		{
			record_collection->erase(first_record, record_it);
			output_file.close(); return file_existed;
		}
	}
	record_collection->erase(first_record, record_it);
	output_file.close(); return file_existed;
}
void RecordFactory::recordDays(std::chrono::time_point<std::chrono::system_clock> day_end)
{
	std::set<RecordFactory::Data_record>::iterator record_it = record_collection->begin();
	RecordFactory::Data_record record_p;

	std::chrono::time_point<std::chrono::system_clock> day;
	std::chrono::time_point<std::chrono::system_clock> next_day;
	std::chrono::days one_day = std::chrono::days(1);

	if (record_collection->size() == 0) { return; }

	while (record_it != record_collection->end())
	{
		record_p = *(record_it);
		day = record_p.toDay();
		next_day = day + one_day;
		recordDay(day, next_day);
		record_it = record_collection->begin();
	}

	return;
}

void RecordFactory::loadRecords(std::string filename)
{
	//std::map<std::pair<std::string, char>, RecordFactory::Data_record*>::const_iterator record_it;
	//RecordFactory::Data_record* record_p;
	std::ifstream dump_file = std::ifstream{ filename };
	RecordFactory::Data_record* record = new Data_record();
	while (dump_file >> *record)// && dump_file.eof())
	{
		record_collection->insert(*record);
		record = new Data_record();
	}
	delete record;
	dump_file.close();
	return;
}

std::ofstream& operator<<(std::ofstream& ost, RecordFactory::Data_record& record)
{
	//std::cout << record.toFile();
	//RecordFactory::Data_record r = record;
	ost << record.toString() << record.toTime_t() << "\n";
	return ost;
}
std::ifstream& operator>>(std::ifstream& ist, RecordFactory::Data_record& record)
{
	std::string devicename;
	char unit;
	std::string data;
	std::time_t timestamp;

	input_name<std::ifstream>(ist, devicename, ",");
	ist >> unit >> data >> timestamp;
	record = RecordFactory::Data_record(devicename, unit, data, timestamp);
	return ist;
}