#include "CL_Menu.h"

std::vector<std::vector<std::string>> CL_Menu::menu_text
{
	{
		"[device name]: Perform that devices one-click action\n1: List devices\n2: Sort by name\n3: Sort by device type(by name as secondary order)\n4[device name] : Select device to interact with it’s full feature set\n5: Add device\n9: Exit\n",
	},
	{
		"1: Update Temperature\n2: Update Humidity\n3: Change device name\n4: Return\n",	//0 : Sensor
		"1: Update Energy Usage\n2: Sleep Timer\n3: Change device name\n4: Return\n",								//1: Socket
	},
};

std::vector<std::string> CL_Menu::sensor_text
{
	"Enter the new Temperature value\n",
	"Enter the new Humidity value\n",
};
std::vector<std::string> CL_Menu::socket_text
{
	"Enter the new Energy usage value\n",
	"Enter how long the socket should Sleep for\n",
};
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

				std::cin >> option_num;
				--option_num;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin >> menu_input;
				}
				else
				{
					try {
						std::cout << sensor_text.at(option_num);
					}
					catch (std::out_of_range) {}

					response_num = sensor_p->TakeInput(option_num);
					if (response_num == 0) { play = false; }
				}
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

				std::cin >> option_num;
				--option_num;
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin >> menu_input;
				}
				else
				{
					try {
						std::cout << socket_text.at(option_num);
					}
					catch (std::out_of_range) {}

					response_num = socket_p->TakeInput(option_num);
					if (response_num == 0) { play = false; }
				}
			}
			break;
	}
	CL_Menu::close();
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