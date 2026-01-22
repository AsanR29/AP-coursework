#include "DeviceFactory.h"
std::string int_to_device[] = {"sensor","socket","light","speaker","thermostat","radiator"};

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

template<>	//make Sensor
Sensor* DeviceFactory::makeDevice(std::string name, int type)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	if (factory->sensor_map.count(name) < 1)
	{
		Sensor* sensor_p = new Sensor(name);
		factory->sensor_map[name] = sensor_p;
		return sensor_p;
	}
	return nullptr;
}
template<>	//make Socket
Socket* DeviceFactory::makeDevice(std::string name, int type)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	if (factory->socket_map.count(name) < 1)
	{
		Socket* socket_p = new Socket(name);
		factory->socket_map[name] = socket_p;
		return socket_p;
	}
	return nullptr;
}
template <>	//make Light
Light* DeviceFactory::makeDevice(std::string name, int type)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	if (factory->light_map.count(name) < 1)
	{
		Light* light_p = new Light(name);
		factory->light_map[name] = light_p;
		return light_p;
	}
	return nullptr;
}
template <> //make Speaker
Speaker* DeviceFactory::makeDevice(std::string name, int type)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	if (factory->speaker_map.count(name) < 1)
	{
		Speaker* speaker_p = new Speaker(name);
		factory->speaker_map[name] = speaker_p;
		return speaker_p;
	}
	return nullptr;
}
template <> //make Thermostat
Thermostat* DeviceFactory::makeDevice(std::string name, int type)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	if (factory->thermostat_map.count(name) < 1)
	{
		Thermostat* thermostat_p = new Thermostat(name);
		factory->thermostat_map[name] = thermostat_p;
		return thermostat_p;
	}
	return nullptr;
}
template <> //make Radiator
Radiator* DeviceFactory::makeDevice(std::string name, int type)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	if (factory->radiator_map.count(name) < 1)
	{
		Radiator* radiator_p = new Radiator(name);
		factory->radiator_map[name] = radiator_p;
		return radiator_p;
	}
	return nullptr;
}
template <>	//make Device
Device* DeviceFactory::makeDevice(std::string name, int type)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	Device* device_p = nullptr;
	switch (type) {
	case 0:
		device_p = DeviceFactory::makeDevice<Sensor>(name);		break;
	case 1:
		device_p = DeviceFactory::makeDevice<Socket>(name);		break;
	case 2:
		device_p = DeviceFactory::makeDevice<Light>(name);		break;
	case 3:
		device_p = DeviceFactory::makeDevice<Speaker>(name);	break;
	case 4:
		device_p = DeviceFactory::makeDevice<Thermostat>(name);	break;
	case 5:
		device_p = DeviceFactory::makeDevice<Radiator>(name);	break;
	}
	return device_p;
}

std::pair<Device*, int> DeviceFactory::getDevice(std::string name)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	Device* found = nullptr;

	int type = 0;
	if (factory->sensor_map.count(name) > 0) {
		found = factory->sensor_map[name];
	}
	if (!found) {
		++type;
		if (factory->socket_map.count(name) > 0) {
			found = factory->socket_map[name];
		}
	}
	if (!found) {
		++type;
		if (factory->light_map.count(name) > 0) {
			found = factory->light_map[name];
		}
	}
	if (!found) {
		++type;
		if (factory->speaker_map.count(name) > 0) {
			found = factory->speaker_map[name];
		}
	}
	if (!found) {
		++type;
		if (factory->thermostat_map.count(name) > 0) {
			found = factory->thermostat_map[name];
		}
	}
	if (!found) {
		++type;
		if (factory->radiator_map.count(name) > 0) {
			found = factory->radiator_map[name];
		}
	}

	return std::make_pair(found, type);
}

bool DeviceFactory::validateDeviceName(std::string name)
{
	//bail on illegal characters found
	if (name.find(":") != std::string::npos) { return false; }
	if (name.find(",") != std::string::npos) { return false; }
	//none found, so return true
	return true;
}

std::string DeviceFactory::TakeDeviceName() {
	std::string new_name;
	bool loop = true;
	while (loop)
	{
		loop = false;
		input_string(new_name);
		if (!validateDeviceName(new_name)) { std::cout << "Invalid device name\n"; loop = true; continue; }
		//originally a switch statement... if any device map contains it, then keep asking for different names
		if (
			(sensor_map.count(new_name) > 0)		||
			(socket_map.count(new_name) > 0)		||
			(light_map.count(new_name) > 0)			||
			(speaker_map.count(new_name) > 0)		||
			(thermostat_map.count(new_name) > 0)	||
			(radiator_map.count(new_name) > 0)
		)
		{ loop = true; }
		if (loop) { std::cout << "That name is already taken"; }
	}
	return new_name;
}

void DeviceFactory::renameDevice(int type, std::string name)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	std::string new_name = factory->TakeDeviceName();

	Sensor* sensor_p;
	Socket* socket_p;
	Light* light_p;
	Speaker* speaker_p;
	Thermostat* thermostat_p;
	Radiator* radiator_p;

	switch (type)
	{
	case 0:	//sensor
		sensor_p = factory->sensor_map[name];		//get the device
		factory->sensor_map.erase(name);
		factory->sensor_map[new_name] = sensor_p;	//put the device under the new name

		sensor_p->updateDeviceName(new_name);		//rename the device itself
		break;
	case 1:
		socket_p = factory->socket_map[name];		//these are all the same process
		factory->socket_map.erase(name);
		factory->socket_map[new_name] = socket_p;
		socket_p->updateDeviceName(new_name);
		break;
	case 2:
		light_p = factory->light_map[name];
		factory->light_map.erase(name);
		factory->light_map[new_name] = light_p;
		light_p->updateDeviceName(new_name);
		break;
	case 3:
		speaker_p = factory->speaker_map[name];
		factory->speaker_map.erase(name);
		factory->speaker_map[new_name] = speaker_p;
		speaker_p->updateDeviceName(new_name);
		break;
	case 4:
		thermostat_p = factory->thermostat_map[name];
		factory->thermostat_map.erase(name);
		factory->thermostat_map[new_name] = thermostat_p;
		thermostat_p->updateDeviceName(new_name);
		break;
	case 5:
		radiator_p = factory->radiator_map[name];
		factory->radiator_map.erase(name);
		factory->radiator_map[new_name] = radiator_p;
		radiator_p->updateDeviceName(new_name);
		break;
	}
	return;
}

#define DELETE_DEVICE(map,type,name)	\
{										\
	type* device_p = map[name];			\
	map.erase(name);					\
	delete device_p;							\
}										\

void DeviceFactory::deleteDevice(int type, std::string name)
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	switch (type)
	{
	case 0:
		DELETE_DEVICE(factory->sensor_map, Sensor, name); break;
	case 1:
		DELETE_DEVICE(factory->socket_map, Socket, name); break;
	case 2:
		DELETE_DEVICE(factory->light_map, Light, name); break;
	case 3:
		DELETE_DEVICE(factory->speaker_map, Speaker, name); break;
	case 4:
		DELETE_DEVICE(factory->thermostat_map, Thermostat, name); break;
	case 5:
		DELETE_DEVICE(factory->radiator_map, Radiator, name); break;
	}
	return;
}

Schedule* DeviceFactory::getSchedule(Device* device, int type)
{
	switch (type) {
		//these are the only types which have schedules
	case 1:
		return dynamic_cast<Socket*>(device)->GetSchedule();
	case 2:
		return dynamic_cast<Light*>(device)->GetSchedule();
	case 4:
		return dynamic_cast<Thermostat*>(device)->GetSchedule();
	case 5:
		return dynamic_cast<Radiator*>(device)->GetSchedule();
	}
	return nullptr;
}

//iterate through each map, run PrintLine() on each device
void DeviceFactory::printDeviceList()
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	std::map<std::string, Sensor*>::const_iterator sensor_it;
	std::map<std::string, Socket*>::const_iterator socket_it;
	std::map < std::string, Light*>::const_iterator light_it;
	std::map < std::string, Speaker*>::const_iterator speaker_it;
	std::map < std::string, Thermostat*>::const_iterator thermostat_it;
	std::map < std::string, Radiator*>::const_iterator radiator_it;

	Sensor* sensor_p;
	Socket* socket_p;
	Light* light_p;
	Speaker* speaker_p;
	Thermostat* thermostat_p;
	Radiator* radiator_p;

	for (sensor_it = factory->sensor_map.cbegin(); sensor_it != factory->sensor_map.cend(); sensor_it++)
	{
		sensor_p = (*sensor_it).second;
		sensor_p->PrintLine(); std::cout << "\n";
	}
	for (socket_it = factory->socket_map.cbegin(); socket_it != factory->socket_map.cend(); socket_it++)
	{
		socket_p = (*socket_it).second;
		socket_p->PrintLine(); std::cout << "\n";
	}
	for (light_it = factory->light_map.cbegin(); light_it != factory->light_map.cend(); light_it++)
	{
		light_p = (*light_it).second;
		light_p->PrintLine(); std::cout << "\n";
	}
	for (speaker_it = factory->speaker_map.cbegin(); speaker_it != factory->speaker_map.cend(); speaker_it++)
	{
		speaker_p = (*speaker_it).second;
		speaker_p->PrintLine(); std::cout << "\n";
	}
	for (thermostat_it = factory->thermostat_map.cbegin(); thermostat_it != factory->thermostat_map.cend(); thermostat_it++)
	{
		thermostat_p = (*thermostat_it).second;
		thermostat_p->PrintLine(); std::cout << "\n";
	}
	for (radiator_it = factory->radiator_map.cbegin(); radiator_it != factory->radiator_map.cend(); radiator_it++)
	{
		radiator_p = (*radiator_it).second;
		radiator_p->PrintLine(); std::cout << "\n";
	}
	return;
}

/*
This version keeps a sorted array (i use a map for this, though)
of the highest priority name of each device map.
It prints the device sorted to the top of that sorted-array, and then retrieves the next
highest priority name from the device's corresponding map, to take its place.
TLDR Its like having 6 queues side by side
*/

#define ITERATE_NAMES(names, map, it, p, type)	\
if(it != map.cend())							\
{												\
	p = (*it).second;							\
	names[p->getName()] = type;					\
	++it;										\
}												\

void DeviceFactory::printDeviceByName()
{
	//setting up the variables
	DeviceFactory* factory = DeviceFactory::getFactory();
	std::map<std::string, Sensor*>::const_iterator sensor_it = factory->sensor_map.cbegin();
	std::map<std::string, Socket*>::const_iterator socket_it = factory->socket_map.cbegin();
	std::map < std::string, Light*>::const_iterator light_it = factory->light_map.cbegin();
	std::map < std::string, Speaker*>::const_iterator speaker_it = factory->speaker_map.cbegin();
	std::map < std::string, Thermostat*>::const_iterator thermostat_it = factory->thermostat_map.cbegin();
	std::map < std::string, Radiator*>::const_iterator radiator_it = factory->radiator_map.cbegin();

	Sensor* sensor_p = nullptr;
	Socket* socket_p = nullptr;
	Light* light_p = nullptr;
	Speaker* speaker_p = nullptr;
	Thermostat* thermostat_p = nullptr;
	Radiator* radiator_p = nullptr;

	std::map<std::string, int> names;
	std::map<std::string, int>::iterator name_it;
	int type;

	//setting up the names map's starting values
	ITERATE_NAMES(names, factory->sensor_map, sensor_it, sensor_p, 0);
	ITERATE_NAMES(names, factory->socket_map, socket_it, socket_p, 1);
	ITERATE_NAMES(names, factory->light_map, light_it, light_p, 2);
	ITERATE_NAMES(names, factory->speaker_map, speaker_it, speaker_p, 3);
	ITERATE_NAMES(names, factory->thermostat_map, thermostat_it, thermostat_p, 4);
	ITERATE_NAMES(names, factory->radiator_map, radiator_it, radiator_p, 5);

	//going through each device map using names
	while (names.size() > 0)
	{
		name_it = names.begin();
		type = (*name_it).second;
		names.erase(name_it);
		switch (type)
		{
		case 0:
			sensor_p->PrintLine(); std::cout << "\n";
			ITERATE_NAMES(names, factory->sensor_map, sensor_it, sensor_p, 0);
			break;
		case 1:
			socket_p->PrintLine(); std::cout << "\n";
			ITERATE_NAMES(names, factory->socket_map, socket_it, socket_p, 1);
			break;
		case 2:
			light_p->PrintLine(); std::cout << "\n";
			ITERATE_NAMES(names, factory->light_map, light_it, light_p, 2);
			break;
		case 3:
			speaker_p->PrintLine(); std::cout << "\n";
			ITERATE_NAMES(names, factory->speaker_map, speaker_it, speaker_p, 3);
			break;
		case 4:
			thermostat_p->PrintLine(); std::cout << "\n";
			ITERATE_NAMES(names, factory->thermostat_map, thermostat_it, thermostat_p, 4);
			break;
		case 5:
			radiator_p->PrintLine(); std::cout << "\n";
			ITERATE_NAMES(names, factory->radiator_map, radiator_it, radiator_p, 5);
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

	for (socket_it = factory->socket_map.begin(); socket_it != factory->socket_map.end(); socket_it++)
	{
		socket_p = (*socket_it).second;
		socket_p->GetSchedule()->setTriggers();
	}
	return;
}

#define ITERATE_CONDS(device_map, it) (it = device_map.begin(); it != device_map.end(); it++)

#define ITERATE_WRITE_DEVICE(device_map, type, stream)			\
{														\
	std::map<std::string, type*>::iterator p_it;		\
	type* p_p;											\
	for ITERATE_CONDS(device_map, p_it)					\
	{													\
		p_p = (*p_it).second;							\
		stream << (*p_p);								\
	}													\
}														\

#define ITERATE_WRITE_SCHEDULE(device_map, type, dstream, sstream)	\
{															\
	std::map<std::string, type*>::iterator p_it;			\
	type* p_p;												\
	for ITERATE_CONDS(device_map, p_it)						\
	{														\
		p_p = (*p_it).second;								\
		dstream << (*p_p);									\
		sstream << p_p->getName();							\
		sstream << *(p_p->GetSchedule());					\
	}														\
}															\

void DeviceFactory::dumpDevices()
{
	DeviceFactory* factory = DeviceFactory::getFactory();

	std::ofstream device_file = std::ofstream{ "Device_store.txt" };
	std::ofstream schedule_file = std::ofstream{ "Schedule_store.txt" };

	device_file << 0 << " " << factory->sensor_map.size() << "\n";
	ITERATE_WRITE_DEVICE(factory->sensor_map, Sensor, device_file);

	device_file << 1 << " " << factory->socket_map.size() << "\n";
	ITERATE_WRITE_SCHEDULE(factory->socket_map, Socket, device_file, schedule_file);

	device_file << 2 << " " << factory->light_map.size() << "\n";
	ITERATE_WRITE_SCHEDULE(factory->light_map, Light, device_file, schedule_file);

	device_file << 3 << " " << factory->speaker_map.size() << "\n";
	ITERATE_WRITE_DEVICE(factory->speaker_map, Speaker, device_file, schedule_file);

	device_file << 4 << " " << factory->thermostat_map.size() << "\n";
	ITERATE_WRITE_SCHEDULE(factory->thermostat_map, Thermostat, device_file, schedule_file);

	device_file << 5 << " " << factory->radiator_map.size() << "\n";
	ITERATE_WRITE_SCHEDULE(factory->radiator_map, Radiator, device_file, schedule_file);

	device_file.close();
	schedule_file.close();
	return;
}
void DeviceFactory::loadDevices()
{
	DeviceFactory* factory = DeviceFactory::getFactory();
	std::ifstream device_file = std::ifstream{ "Device_store.txt" };

	int type;
	int device_count;

	Sensor* sensor_p;
	Socket* socket_p;
	Light* light_p;
	Speaker* speaker_p;
	Thermostat* thermostat_p;
	Radiator* radiator_p;

	std::string devicename;

	while (device_file.good())
	{
		device_file >> type >> device_count;
		if (device_file.fail())
		{
			device_file.close();
			break;
		}
		switch (type)
		{
		case 0:
			for (int i = 0; i < device_count; i++)
			{
				input_name<std::ifstream>(device_file, devicename, ",");
				sensor_p = makeDevice<Sensor>(devicename);
				device_file >> (*sensor_p);
			}
			break;
		case 1:
			for (int i = 0; i < device_count; i++)
			{
				input_name<std::ifstream>(device_file, devicename, ",");
				socket_p = makeDevice<Socket>(devicename);
				device_file >> (*socket_p);
			}
			break;
		case 2:
			for (int i = 0; i < device_count; i++)
			{
				input_name<std::ifstream>(device_file, devicename, ",");
				light_p = makeDevice<Light>(devicename);
				device_file >> (*light_p);
			}
			break;
		case 3:
			for (int i = 0; i < device_count; i++)
			{
				input_name<std::ifstream>(device_file, devicename, ",");
				speaker_p = makeDevice<Speaker>(devicename);
				device_file >> (*speaker_p);
			}
			break;
		case 4:
			for (int i = 0; i < device_count; i++)
			{
				input_name<std::ifstream>(device_file, devicename, ",");
				thermostat_p = makeDevice<Thermostat>(devicename);
				device_file >> (*thermostat_p);
			}
			break;
		case 5:
			for (int i = 0; i < device_count; i++)
			{
				input_name<std::ifstream>(device_file, devicename, ",");
				radiator_p = makeDevice<Radiator>(devicename);
				device_file >> (*radiator_p);
			}
			break;
		}
	}

	std::ifstream schedule_file = std::ifstream{ "Schedule_store.txt" };
	int trigger_count;
	std::pair<Device*, int> d_subject;
	Schedule* schedule_p;

	int trigger_type;
	int minutes;
	while (schedule_file.good())
	{
		schedule_file >> devicename >> trigger_count;
		if (schedule_file.fail())
		{
			schedule_file.close();
			break;
		}
		d_subject = DeviceFactory::getDevice(devicename);
		schedule_p = DeviceFactory::getSchedule(d_subject.first, d_subject.second);
		for (int i = 0; i < trigger_count; i++)
		{
			schedule_file >> trigger_type >> minutes;
			schedule_p->addTrigger(d_subject.first, trigger_type, std::chrono::minutes(minutes));
		}
	}
	return;
}

#define ITERATE_DELETE(device_map, type)				\
{														\
	std::map<std::string, type*>::iterator device_it;	\
	type* device_p;										\
	for ITERATE_CONDS(device_map, device_it)			\
	{													\
		device_p = (*device_it).second;					\
		delete device_p;								\
	}													\
}														\

DeviceFactory::~DeviceFactory()
{
	ITERATE_DELETE(sensor_map, Sensor);
	ITERATE_DELETE(socket_map, Socket);
	ITERATE_DELETE(light_map, Light);
	ITERATE_DELETE(speaker_map, Speaker);
	ITERATE_DELETE(thermostat_map, Thermostat);
	ITERATE_DELETE(radiator_map, Radiator);
	
	return;
}
void DeviceFactory::clear()
{
	delete instantiation;
}