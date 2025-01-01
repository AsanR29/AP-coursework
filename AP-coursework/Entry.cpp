#include "RecordFactory.h"
#include "DeviceFactory.h"
#include "Testees.h"
#include "CL_Menu.h"


void shutdown(Testees* test)
{
	delete test;

	RecordFactory::dumpRecords();

	RecordFactory::clear();
	DeviceFactory::clear();
}

int main()
{

	//populating with test devices
	Testees::loadFile("animal_names.csv");
	Testees* test = new Testees();

	int rand_type;
	int capacity = (test->nleft > 10) ? test->nleft - 10 : 0;
	while (test->nleft > capacity)
	{
		rand_type = rand() % 2;
		if (rand_type == 0)
		{
			DeviceFactory::makeDevice("sensor", test->popName());
		}
		else if (rand_type == 1)
		{
			DeviceFactory::makeDevice("socket", test->popName());
		}
	}

	//program starts
	CL_Menu::makeMenu(0,0);
	CL_Menu* menu = CL_Menu::get();

	bool play = true;
	std::string menu_input;
	int option_num;

	std::pair<Device*, int> d_subject;
	while (play)
	{
		option_num = -1;

		menu->PrintLine();
		std::cin >> option_num;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin >> menu_input;
		}
		if (option_num == 4)
		{
			std::cin >> menu_input;
		}
		switch (option_num)
		{
		case -1:
			break;
		case 1:
			DeviceFactory::printDeviceList();
			break;
		case 4:
			d_subject = DeviceFactory::getDevice(menu_input);
			if (d_subject.first != nullptr)
			{
				CL_Menu::makeMenu(d_subject);
				menu = CL_Menu::get();
			}
			else
			{
				std::cout << "Couldn't find a device by that name\n";
			}
			break;
		case 9:
			play = false;
			break;
		}
		std::cout << "\n" << option_num << menu_input << "\n";
	}

	shutdown(test);

	return 0;
}