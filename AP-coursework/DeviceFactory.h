#pragma once
#include <map>
#include <iostream>

#include "Sensor.h"
#include "Socket.h"
#include "Light.h"
#include "Speaker.h"
#include "Thermostat.h"
#include "Radiator.h"

class DeviceFactory
{
private:
	std::map<std::string, Sensor*> sensor_map;
	std::map<std::string, Socket*> socket_map;
	std::map<std::string, Light*> light_map;
	std::map<std::string, Speaker*> speaker_map;
	std::map<std::string, Thermostat*> thermostat_map;
	std::map<std::string, Radiator*> radiator_map;

	//DeviceFactory();
	static DeviceFactory* instantiation;
public:
	static DeviceFactory* getFactory();

	static std::pair<Device*, int> getDevice(std::string name);

	template <class device_type>
	static device_type* makeDevice(std::string name, int type = -1);

	static void renameDevice(int type, std::string name);
	static void deleteDevice(int type, std::string name);

	static Schedule* getSchedule(Device* device, int type);

	static void printDeviceList();
	static void printDeviceByName();
	static void setSchedules();

	static void dumpDevices();
	static void loadDevices();
	static void clear();

	std::string TakeDeviceName();
	inline static bool validateDeviceName(std::string name);

	static std::string int_to_device[];

	~DeviceFactory();
};

