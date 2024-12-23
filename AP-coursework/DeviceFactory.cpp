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

Device* DeviceFactory::getDevice(std::string name)
{
	Device* found = nullptr;
	DeviceFactory* factory = DeviceFactory::getFactory();

	found = factory->sensor_map[name];
	if (!found) { found = factory->socket_map[name]; }
	//if (!found) { found = factory->radiator_map[name]; }
	//etc
	
	return found;
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
	//std::map<std::string, Socket*>::iterator socket_it;
	Sensor* sensor_p;
	for (sensor_it = factory->sensor_map.begin(); sensor_it != factory->sensor_map.end(); sensor_it++)
	{
		sensor_p = (*sensor_it).second;
		//std::cout << "Sensor:\n";
		sensor_p->PrintLine();
		std::cout << "\n";
	}
	return;
}