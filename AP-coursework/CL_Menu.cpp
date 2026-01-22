#include "CL_Menu.h"

//static data members
std::stack<CL_Menu> CL_Menu::menu_stack;
std::vector<std::vector<std::string>> CL_Menu::menu_text
{
	{	//main menu
		"[device name]: Perform that devices one-click action\n1: List devices\n2: Sort by name\n3: Sort by device type(by name as secondary order)\n4[device name] : Select device to interact with it’s full feature set\n5: Add device\n9: Exit\n",
	},
	{	//menus for each opened device (following main menu option 4)
		"1: Update Temperature\n2: Update Humidity\n3: Change device name\n4: Delete device\n5: Return\n",				//0: Sensor
		"1: Update Energy Usage\n2: Sleep Timer\n3: Change device name\n4: Delete device\n5: Return\n",					//1: Socket
		"1: Adjust Brightness\n2: Sleep Timer\n3: Change device name\n4: Delete device\n5: Return\n",					//2: Light
		"1: Adjust Volume\n2: Change device name\n3: Delete device\n4: Return\n",										//3: Speaker
		"1: Activate Heating boost\n2: Adjust Schedule\n3: Change device name\n4: Delete device\n5: Return\n",			//4: Thermostat
		"1: Update Current temperature\n2: Adjust Schedule\n3: Change device name\n4: Delete device\n5: Return\n",		//5: Radiator
		//menu following main menu option 5
		"1: Add sensor\n2: Add Socket\n3: Add Light\n4: Add Speaker\n5: Add Thermostat\n6: Add Radiator\n7: Return\n",	//6: Make Device
		//menus for opened schedules & sleep timers
		"1: Display Sleep Schedule\n2: Add Sleep Interval\n3: Clear data\n4: Return\n",					//7: Sleep Timer schedule menu
		"1: Display Function Schedule\n2: Schedule additional functions\n3: Clear data\n4: Return\n",	//8: On/Off schedule menu
	},
};

//menus prompting TakeInput() for each device
std::vector<std::string> CL_Menu::sensor_text
{
	"Enter the new Temperature value\n",
	"Enter the new Humidity value\n",
	"Enter the new Device name\n",
	"Deleted\n",
};
std::vector<std::string> CL_Menu::socket_text
{
	"Enter the new Energy usage value\n",
	"\n",
	"Enter the new Device name\n",
	"Deleted\n",
};
std::vector<std::string> CL_Menu::light_text
{
	"Enter the new level of Brightness\n",
	"\n",
	"Enter the new Device name\n",
	"Deleted\n",
};
std::vector<std::string> CL_Menu::speaker_text
{
	"Enter the new volume level\n",
	"Enter the new Device name\n",
	"Deleted\n",
};
std::vector<std::string> CL_Menu::thermostat_text
{
	"Heating boost turned on\n",
	"\n",
	"Enter the new Device name\n",
	"Deleted\n",
};
std::vector<std::string> CL_Menu::radiator_text
{
	"Enter the current Temperature\n",
	"\n",
	"Enter the new Device name\n",
	"Deleted\n",
};

std::vector<std::string> CL_Menu::schedule_text
{
	"\n",
	"\n",
	"Cleared\n",
};

//constructor
CL_Menu::CL_Menu(int a, int b)
{
	id = std::make_pair(a, b);
};

//controllers for the constructor
void CL_Menu::makeMenu(int a, int b)
{
	CL_Menu m(a, b);
	menu_stack.push(m);
	return;
}

//menu which closes itself
void CL_Menu::makeMenu(std::pair<Device*, int> subject)	//this parameter is the direct output of DeviceFactory::getDevice
{
	CL_Menu::makeMenu(1, subject.second);
	CL_Menu* menu = CL_Menu::get();

	bool play = true;
	std::string menu_input;
	int option_num;
	int response_num;

	switch (subject.second)
	{
		case 0:
			Sensor * sensor_p;
			sensor_p = dynamic_cast<Sensor*>(subject.first);

			while (play)
			{
				//setup, then output menu
				option_num = -1;
				std::cout << sensor_p->tagline() << "\n";
				menu->PrintLine();

				input_int(option_num);
				//return menu's response to the input
				--option_num;
				if (option_num == 3) {
					DeviceFactory::deleteDevice(subject.second, sensor_p->getName());
					CL_Menu::close();
					return;
				}
				if(0 <= option_num && option_num < 5){
					if (option_num != 4) { std::cout << sensor_text.at(option_num); }

					//perform action requested by the input
					response_num = sensor_p->TakeInput(option_num);
					//actions outside the Device's scope
					if (response_num == 2) { DeviceFactory::renameDevice(subject.second, sensor_p->getName()); }
					if (response_num == 0) { play = false; }
				}
			}
			break;
		case 1:	//Socket
			Socket * socket_p;
			socket_p = dynamic_cast<Socket*>(subject.first);
			while (play)
			{
				//setup, then output menu
				option_num = -1;
				std::cout << socket_p->tagline() << "\n";
				menu->PrintLine();

				input_int(option_num);
				//return menu's response to the input
				--option_num;
				if (option_num == 3) {
					DeviceFactory::deleteDevice(subject.second, socket_p->getName());
					CL_Menu::close();
					return;
				}
				if(0 <= option_num && option_num < 5){
					if (option_num != 4) { std::cout << socket_text.at(option_num); }

					//perform action requested by the input
					response_num = socket_p->TakeInput(option_num);
					//actions outside the Device's scope
					if (response_num == 2) { DeviceFactory::renameDevice(subject.second, socket_p->getName()); }
					if (response_num == 3) {
						CL_Menu::scheduleMenu(socket_p->GetSchedule(), subject.first, 7);
						menu = CL_Menu::get();
					}
					if (response_num == 0) { play = false; }
				}
			}
			break;
		case 2:	//Light
			Light * light_p;
			light_p = dynamic_cast<Light*>(subject.first);
			while (play)
			{
				//setup, then output menu
				option_num = -1;
				std::cout << light_p->tagline() << "\n";
				menu->PrintLine();

				input_int(option_num);
				//return menu's response to the input
				--option_num;
				if (option_num == 3) {
					DeviceFactory::deleteDevice(subject.second, light_p->getName());
					CL_Menu::close();
					return;
				}
				if (0 <= option_num && option_num < 5) {
					if (option_num != 4) { std::cout << light_text.at(option_num); }

					//perform action requested by the input
					response_num = light_p->TakeInput(option_num);
					//actions outside the Device's scope
					if (response_num == 2) { DeviceFactory::renameDevice(subject.second, light_p->getName()); }
					if (response_num == 3) {
						CL_Menu::scheduleMenu(light_p->GetSchedule(), subject.first, 7);
						menu = CL_Menu::get();
					}
					if (response_num == 0) { play = false; }
				}
			}
		case 3:	//Speaker
			Speaker * speaker_p;
			speaker_p = dynamic_cast<Speaker*>(subject.first);
			while (play)
			{
				//setup, then output menu
				option_num = -1;
				std::cout << speaker_p->tagline() << "\n";
				menu->PrintLine();

				input_int(option_num);
				//return menu's response to the input
				--option_num;
				if (option_num == 2) {
					DeviceFactory::deleteDevice(subject.second, speaker_p->getName());
					CL_Menu::close();
					return;
				}
				if (0 <= option_num && option_num < 4) {
					if (option_num != 3) { std::cout << speaker_text.at(option_num); }

					//perform action requested by the input
					response_num = speaker_p->TakeInput(option_num);
					//actions outside the Device's scope
					if (response_num == 2) { DeviceFactory::renameDevice(subject.second, speaker_p->getName()); }
					if (response_num == 0) { play = false; }
				}
			}
			break;
		case 4:
			Thermostat * thermostat_p;
			thermostat_p = dynamic_cast<Thermostat*>(subject.first);
			while (play)
			{
				//setup, then output menu
				option_num = -1;
				std::cout << thermostat_p->tagline() << "\n";
				menu->PrintLine();

				input_int(option_num);
				//return menu's response to the input
				--option_num;
				if (option_num == 3) {
					DeviceFactory::deleteDevice(subject.second, thermostat_p->getName());
					CL_Menu::close();
					return;
				}
				if (0 <= option_num && option_num < 5) {
					if (option_num != 4) { std::cout << thermostat_text.at(option_num); }

					//perform action requested by the input
					response_num = thermostat_p->TakeInput(option_num);
					//actions outside the Device's scope
					if (response_num == 2) { DeviceFactory::renameDevice(subject.second, thermostat_p->getName()); }
					if (response_num == 3) {
						CL_Menu::scheduleMenu(thermostat_p->GetSchedule(), subject.first, 8);
						menu = CL_Menu::get();
					}
					if (response_num == 0) { play = false; }
				}
			}
			break;
		case 5:
			Radiator * radiator_p;
			radiator_p = dynamic_cast<Radiator*>(subject.first);
			while (play)
			{
				//setup, then output menu
				option_num = -1;
				std::cout << radiator_p->tagline() << "\n";
				menu->PrintLine();

				input_int(option_num);
				//return menu's response to the input
				--option_num;
				if (option_num == 3) {
					DeviceFactory::deleteDevice(subject.second, radiator_p->getName());
					CL_Menu::close();
					return;
				}
				if (0 <= option_num && option_num < 5) {
					if (option_num != 4) { std::cout << radiator_text.at(option_num); }

					//perform action requested by the input
					response_num = radiator_p->TakeInput(option_num);
					//actions outside the Device's scope
					if (response_num == 2) { DeviceFactory::renameDevice(subject.second, radiator_p->getName()); }
					if (response_num == 3) {
						CL_Menu::scheduleMenu(radiator_p->GetSchedule(), subject.first, 8);
						menu = CL_Menu::get();
					}
					if (response_num == 0) { play = false; }
				}
			}
			break;
	}
	CL_Menu::close();
	return;
}

void CL_Menu::newDeviceMenu()
{
	int type = -1;
	while (type < 1 || type > 7)
	{
		input_int(type);
	}
	--type;
	if (type == 6) { return; }

	DeviceFactory* factory = DeviceFactory::getFactory();
	std::cout << "Enter the new Device name\n";
	std::string device_name = factory->TakeDeviceName();
	Device* subject_d = DeviceFactory::makeDevice<Device>(device_name, type);

	CL_Menu::makeMenu(std::make_pair(subject_d, type));
	return;
}

void CL_Menu::scheduleMenu(Schedule* schedule, Device* device, int type)
{
	CL_Menu::makeMenu(1, type);
	CL_Menu* menu = CL_Menu::get();
	type -= 7;

	bool play = true;
	std::string menu_input;
	int option_num;
	int response_num;

	while (play)
	{
		option_num = -1;

		std::cout << device->tagline() << "\n";
		menu->PrintLine();

		input_int(option_num);
		--option_num;
		if (0 <= option_num && 3 >= option_num) {
			if (option_num < 3) { std::cout << schedule_text.at(option_num); }
			response_num = schedule->TakeInput(device, option_num, type);
			if (response_num == 0) { play = false; }
		}
		//catch (std::out_of_range) {}
	}
	CL_Menu::close();
	return;
}

//menu stack methods
CL_Menu* CL_Menu::get()
{
	CL_Menu* m = &CL_Menu::menu_stack.top();
	return m;
}
void CL_Menu::close()
{
	CL_Menu::menu_stack.pop();
	system("cls");
	return;
}
void CL_Menu::clear()
{
	while (!CL_Menu::menu_stack.empty())
	{
		CL_Menu::menu_stack.pop();
	}
	return;
}

//the menu's most important method
//literally using its data to dictate the output
void CL_Menu::PrintLine()
{
	std::cout << menu_text.at(id.first).at(id.second);
	return;
}