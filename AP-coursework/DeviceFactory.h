#pragma once
#include <map>
#include <iostream>

#include "Sensor.h"
#include "Socket.h"

class DeviceFactory
{
private:
	std::map<std::string, Sensor*> sensor_map;
	std::map<std::string, Socket*> socket_map;

	//DeviceFactory();
	static DeviceFactory* instantiation;
public:
	static DeviceFactory* getFactory();

	static std::pair<Device*, int> getDevice(std::string name);
	static Device* makeDevice(std::string type, std::string name);

	static void printDeviceList();

	static void clear();

	~DeviceFactory();
};

