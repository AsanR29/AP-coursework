#include "DeviceFactory.h"

//singleton
DeviceFactory* DeviceFactory::instantiation = nullptr;
DeviceFactory* DeviceFactory::getFactory()
{
	if (!instantiation)
	{
		instantiation = new DeviceFactory();
	}
	return instantiation;
}

std::pair<Device*,int> DeviceFactory::getDevice(std::string name)
{
	int type = 0;
	Device* found = nullptr;
	DeviceFactory* factory = DeviceFactory::getFactory();

	if (factory->sensor_map.count(name) > 0)
	{
		found = factory->sensor_map[name];
	}
	
	if (!found) {
		if (factory->socket_map.count(name) > 0)
		{
			found = factory->socket_map[name]; ++type;
		}
	}
	//if (!found) { found = factory->radiator_map[name]; ++type; }
	//etc
	
	return std::make_pair(found, type);
}

Device* DeviceFactory::makeDevice(std::string type, std::string name)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	if (type == "sensor") {
		if (factory->sensor_map.count(name) < 1)
		{
			Sensor* a = new Sensor(name);
			factory->sensor_map[name] = a;
			return a;
		}
	}
	else if (type == "socket") {
		if (factory->socket_map.count(name) < 1)
		{
			Socket* a = new Socket(name);
			factory->socket_map[name] = a;
			return a;
		}
	}
	return nullptr;
}

void DeviceFactory::printDeviceList()
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	std::map<std::string, Sensor*>::iterator sensor_it;
	std::map<std::string, Socket*>::iterator socket_it;

	Sensor* sensor_p;
	Socket* socket_p;

	for (sensor_it = factory->sensor_map.begin(); sensor_it != factory->sensor_map.end(); sensor_it++)
	{
		sensor_p = (*sensor_it).second;
		sensor_p->PrintLine();
		std::cout << "\n";
	}
	for (socket_it = factory->socket_map.begin(); socket_it != factory->socket_map.end(); socket_it++)
	{
		socket_p = (*socket_it).second;
		socket_p->PrintLine();
		std::cout << "\n";
	}
	return;
}

DeviceFactory::~DeviceFactory()
{
	std::map<std::string, Sensor*>::iterator sensor_it;
	std::map<std::string, Socket*>::iterator socket_it;

	Sensor* sensor_p;
	Socket* socket_p;

	for (sensor_it = sensor_map.begin(); sensor_it != sensor_map.end(); sensor_it++)
	{
		sensor_p = (*sensor_it).second;
		delete sensor_p;
	}
	for (socket_it = socket_map.begin(); socket_it != socket_map.end(); socket_it++)
	{
		socket_p = (*socket_it).second;
		delete socket_p;
	}
	return;
}
void DeviceFactory::clear()
{
	delete instantiation;
}