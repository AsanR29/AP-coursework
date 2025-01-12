#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <map>

class Device
{
private:
protected:
	std::string _name;
	bool status;	//true=on, false=off

	void Oneclick();
public:
	Device();
	Device(std::string name);
	Device(std::string name, bool status);
	std::string getName();
	void updateDeviceName(std::string);

	virtual void PrintLine() = 0;
	virtual std::string tagline() = 0;
	virtual int TakeInput(int) = 0;
	void OneClick();
	void On();
	void Off();
};

//int input_int();
void input_int(int& output);
void input_int(int& output, std::string error_response);
void input_timeofday(int& output_hour, int& output_min, std::string error_response);
void input_int_inrange(int& output, int max_included);
void input_string(std::string& output);

template<typename stream>
void input_name(stream& st, std::string& output, std::string delimiter)
{
	output = "";
	std::string inp{ "" };
	bool space = false;
	while (st >> inp)
	{
		if (inp == delimiter) { break; }
		if (space) { output += " "; }
		output += inp;
		space = true;
	}
	return;
}