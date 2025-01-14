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
	//data members
	std::string _name;
	bool status;	//true=on, false=off

public:
	//constructors
	Device();
	Device(std::string name);
	Device(std::string name, bool status);

	//Getters
	std::string getName();
	inline std::string tellStatus()
	{
		return ((status) ? " Status:On" : "Status:Off");
	}

	//Setter for _name
	void updateDeviceName(std::string);
	//Setters for status
	void OneClick();
	void On();
	void Off();

	//subclass defined
	virtual void PrintLine() = 0;
	virtual std::string tagline() = 0;
	virtual int TakeInput(int) = 0;
};

//Most classes have access to Device.h
//Classes which interact with a Device often need methods like these

//command line input ints
void input_int(int& output);
void input_int_inrange(int& output, int max_included);

//used by functions called within TakeInput for ints and doubles
template <typename number>
void input_number(number& output, std::string error_response)
{
	std::string dump;
	output = -1;
	std::cin >> output;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin >> dump;

		std::cout << error_response;
		std::cin >> output;
	}
	return;
}

//used to create a duration offset from the beginning of a day
void input_timeofday(int& output_hour, int& output_min, std::string error_response);

void input_string(std::string& output);

//input from file
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