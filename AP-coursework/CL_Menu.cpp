#include "CL_Menu.h"

std::vector<std::vector<std::string>> CL_Menu::menu_text
{
	{
		"[device name]: Perform that devices one-click action\n1: List devices\n2: Sort by name\n3: Sort by device type(by name as secondary order)\n4[device name] : Select device to interact with it’s full feature set\n5: Add device\n9: Exit\n",
	},
	{
		"1: Update Temperature\n2: Update Humidity\n3: Change device name\n4: Return\n",				//0 : Sensor
		"1: Update Energy Usage\n2: Sleep Timer\n3: Change device name\n4: Return\n",					//1: Socket
		"",	//2
		"",	//3
		"",	//4
		"",	//5
		"1: Add sensor\n2: Add Socket\n3: Add X\n4: Add X\n5: Add X\n6: Add X\n7: Return\n",			//6: Make Device
		"1: Display Sleep Schedule\n2: Add Sleep Interval\n3: Clear data\n4: Return\n",					//7: Sleep Timer schedule menu
		"1: Display Function Schedule\n2: Schedule additional functions\n3: Clear data\n4: Return\n",	//8: On/Off schedule menu
	},
};

std::vector<std::string> CL_Menu::sensor_text
{
	"Enter the new Temperature value\n",
	"Enter the new Humidity value\n",
	"Enter the new Device name\n",
};
std::vector<std::string> CL_Menu::socket_text
{
	"Enter the new Energy usage value\n",
	"\n",
	"Enter the new Device name\n",
};
std::vector<std::string> CL_Menu::schedule_text
{
	"\n",
	"Enter when the Socket should begin sleeping from, in [23:59] format\n",
	"Cleared\n",
}
//void (Sensor::*sensor_f1)() = &Sensor::updateTemperature;
//typedef void (Sensor::* function_p)(void);
//std::vector<function_p> CL_Menu::sensor_functions
//{
//	&Sensor::updateTemperature,		//0
//	&Sensor::updateHumidity,		//1
//};

std::stack<CL_Menu> CL_Menu::menu_stack;

CL_Menu::CL_Menu(int a, int b)
{
	id = std::make_pair(a, b);
};
void CL_Menu::makeMenu(int a, int b)
{
	CL_Menu m(a, b);
	menu_stack.push(m);
	return;
}

void CL_Menu::makeMenu(std::pair<Device*, int> subject)
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
				option_num = -1;

				std::cout << sensor_p->tagline() << "\n";
				menu->PrintLine();

				input_int(option_num);
				--option_num;
				if(0 <= option_num && 3 >= option_num){
					if (option_num < 3) { std::cout << sensor_text.at(option_num); }
					response_num = sensor_p->TakeInput(option_num);
					if (response_num == 2) { DeviceFactory::renameDevice(subject.second, sensor_p->getName()); }
					if (response_num == 0) { play = false; }
				}
				//catch (std::out_of_range) {}
			}
			break;
		case 1:	//Socket
			Socket * socket_p;
			socket_p = dynamic_cast<Socket*>(subject.first);
			while (play)
			{
				option_num = -1;

				std::cout << socket_p->tagline() << "\n";
				menu->PrintLine();

				input_int(option_num);
				--option_num;
				if(0 <= option_num && 3 >= option_num){
					if (option_num < 3) { std::cout << socket_text.at(option_num); }
					response_num = socket_p->TakeInput(option_num);
					if (response_num == 2) { DeviceFactory::renameDevice(subject.second, socket_p->getName()); }
					if (response_num == 3) { CL_Menu::scheduleMenu(socket_p->GetSchedule(), subject.first, 7); }
					if (response_num == 0) { play = false; }
				}
				//catch (std::out_of_range) {}
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
	std::string device_name = factory->TakeDeviceName(type);
	Device* subject_d = DeviceFactory::makeDevice(type, device_name);

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
	return;
}

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

void CL_Menu::PrintLine()
{
	std::cout << menu_text.at(id.first).at(id.second);
	return;
}