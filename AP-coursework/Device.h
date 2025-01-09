#pragma once
#include <iostream>
#include <string>
#include <chrono>

class Device
{
private:
protected:
	std::string _name;
	bool status;	//true=on, false=off

	void TakeDeviceName();
	void Oneclick();
public:
	Device();
	Device(std::string);
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