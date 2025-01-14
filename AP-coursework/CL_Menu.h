#pragma once

#include <stack>
#include <vector>
#include <iostream>

//devices
#include "DeviceFactory.h"
class CL_Menu
{
private:
	//static data members
	//a stack of CL_Menus (ids (int coords))
	static std::stack<CL_Menu> menu_stack;	
	//these are all just strings
	static std::vector<std::vector<std::string>> menu_text;

	static std::vector<std::string> sensor_text;	//0: sensor
	static std::vector<std::string> socket_text;	//1: socket
	static std::vector<std::string> light_text;		//2: light
	static std::vector<std::string> speaker_text;	//3: speaker
	static std::vector<std::string> thermostat_text;//4: thermostat
	static std::vector<std::string> radiator_text;	//5: radiator

	static std::vector<std::string> schedule_text;

	//non-static data member
	std::pair<int,int> id;	//id is coordinate on menu_text, and what is really being stored on the menu_stack

	//constructor
	CL_Menu(int a, int b);
public:
	//constructor controllers
	static void makeMenu(int a, int b);
	static void makeMenu(std::pair<Device*, int>);
	static void scheduleMenu(Schedule*, Device*, int);
	void newDeviceMenu();

	//menu_stack methods
	static CL_Menu* get();
	static void close();
	static void clear();

	//output the menu!
	void PrintLine();
};
//this is messy because its awkward to actually put each one of those device menus, like "socket_text" and "thermostat_text"
//into the same collection as menu_text with it as a vector
//so right now its like a dialogue tree except all of the branches are cut off and stored at the base