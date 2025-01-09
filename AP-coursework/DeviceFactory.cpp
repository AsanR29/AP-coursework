#include "DeviceFactory.h"
std::string int_to_device[] = {"sensor","socket"};

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

Device* DeviceFactory::makeDevice(int type, std::string name)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	switch (type)
	{
	case 0:
		if (factory->sensor_map.count(name) < 1)
		{
			Sensor* sensor_p = new Sensor(name);
			factory->sensor_map[name] = sensor_p;
			return sensor_p;
		}
		break;
	case 1:
		if (factory->socket_map.count(name) < 1)
		{
			Socket* socket_p = new Socket(name);
			factory->socket_map[name] = socket_p;
			return socket_p;
		}
		break;
	}
	
	return nullptr;
}

bool DeviceFactory::validateDeviceName(std::string name)
{
	if (name.find(":") != std::string::npos) { return false; }
	return true;
}

std::string DeviceFactory::TakeDeviceName(int type) {
	std::string new_name;
	bool loop = true;
	while (loop)
	{
		std::cin >> new_name;
		if (!validateDeviceName(new_name)) { std::cout << "Invalid device name\n"; continue; }
		switch (type)
		{
		case 0:
			if (sensor_map.count(new_name) < 1) { loop = false; } 
			break;
		case 1:
			if (socket_map.count(new_name) < 1) { loop = false; }
			break;
		}
	}
	return new_name;
}

void DeviceFactory::renameDevice(int type, std::string name)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	std::string new_name = factory->TakeDeviceName(type);

	Sensor* sensor_p;
	Socket* socket_p;

	switch (type)
	{
	case 0:	//sensor
		sensor_p = factory->sensor_map[name];
		factory->sensor_map.erase(name);
		factory->sensor_map[new_name] = sensor_p;

		sensor_p->updateDeviceName(new_name);
		break;
	case 1:
		socket_p = factory->socket_map[name];
		factory->socket_map.erase(name);
		factory->socket_map[new_name] = socket_p;

		socket_p->updateDeviceName(new_name);
		break;
	}
	return;
}

void DeviceFactory::printDeviceList()
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	std::map<std::string, Sensor*>::const_iterator sensor_it;
	std::map<std::string, Socket*>::const_iterator socket_it;

	Sensor* sensor_p;
	Socket* socket_p;

	for (sensor_it = factory->sensor_map.cbegin(); sensor_it != factory->sensor_map.cend(); sensor_it++)
	{
		sensor_p = (*sensor_it).second;
		sensor_p->PrintLine();
		std::cout << "\n";
	}
	for (socket_it = factory->socket_map.cbegin(); socket_it != factory->socket_map.cend(); socket_it++)
	{
		socket_p = (*socket_it).second;
		socket_p->PrintLine();
		std::cout << "\n";
	}
	return;
}
void DeviceFactory::printDeviceByName()
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	std::map<std::string, Sensor*>::const_iterator sensor_it = factory->sensor_map.begin();
	std::map<std::string, Socket*>::const_iterator socket_it = factory->socket_map.begin();

	Sensor* sensor_p;
	Socket* socket_p;

	int pickme;
	std::string names[2];	//change to names[4]
	bool non_empty[2]{ true,true };		//change to non_empty[4]
	names[0] = (sensor_it != factory->sensor_map.end()) ? ((*sensor_it).second)->getName() : ":";
	names[1] = (socket_it != factory->socket_map.end()) ? ((*socket_it).second)->getName() : ":";
	//++sensor_it; ++socket_it;
	if (names[0] == ":") { non_empty[0] = false; }
	if (names[1] == ":") { non_empty[1] = false; }
	while (non_empty[0] || non_empty[1])
	{
		pickme = -1;
		pickme = (!non_empty[0]) ? pickme : 0;
		//std::cout << "\n" << names[pickme] << " vs " << names[1] << ((names[pickme] < names[1]) ? " less " : " not-less ") << ", Overall:" << (!non_empty[1] || (pickme != -1 && names[pickme] < names[1]) ? " less\n" : " not-less\n");
		pickme = (!non_empty[1] || (pickme !=-1 && names[pickme] < names[1])) ? pickme : 1;
		
		//pickme = (pickme != -1 && !non_empty[2] && names[pickme] < names[2]) ? pickme : 2;
		//pickme = (pickme != -1 && !non_empty[3] && names[pickme] < names[3]) ? pickme : 3;
		switch (pickme)
		{
		case 0:
			sensor_p = (*sensor_it).second;
			sensor_p->PrintLine();
			std::cout << "\n";
			++sensor_it;
			if (sensor_it != factory->sensor_map.end()) { names[0] = ((*sensor_it).second)->getName(); }
			else { non_empty[0] = false; }
			break;
		case 1:
			socket_p = (*socket_it).second;
			socket_p->PrintLine();
			std::cout << "\n";
			++socket_it;
			if (socket_it != factory->socket_map.end()) { names[1] = ((*socket_it).second)->getName(); }
			else { non_empty[1] = false; }
			break;
		}
	}
	return;

}

void DeviceFactory::setSchedules()
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	std::map<std::string, Socket*>::iterator socket_it;

	Socket* socket_p;

	//Schedule* schedule;
	for (socket_it = factory->socket_map.begin(); socket_it != factory->socket_map.end(); socket_it++)
	{
		socket_p = (*socket_it).second;
		socket_p->GetSchedule()->setTriggers();
		//schedule->setTriggers();
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