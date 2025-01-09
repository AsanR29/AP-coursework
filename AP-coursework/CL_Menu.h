#pragma once

#include <stack>
#include <vector>
#include <iostream>

//devices
#include "DeviceFactory.h"
class CL_Menu
{
private:
	static std::vector<std::vector<std::string>> menu_text;
	//static std::vector<void (Sensor::*)()> sensor_functions;
	static std::vector<std::string> sensor_text;
	static std::vector<std::string> socket_text;
	static std::vector<std::string> schedule_text;

	std::pair<int,int> id;
	CL_Menu(int a, int b);
public:
	static std::stack<CL_Menu> menu_stack;
	static void makeMenu(int a, int b);
	static void makeMenu(std::pair<Device*, int>);
	static void scheduleMenu(Schedule*, Device*, int);

	//static int input_int();

	static CL_Menu* get();
	static void close();
	static void clear();

	void newDeviceMenu();

	void PrintLine();

};

