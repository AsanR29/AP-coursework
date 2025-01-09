#include "RecordFactory.h"
#include "DeviceFactory.h"
#include "Testees.h"
#include "CL_Menu.h"

void updatetime()
{
	std::chrono::time_point<std::chrono::system_clock> present_time = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> present_day = std::chrono::floor<std::chrono::days>(present_time);

	TriggerFactory::updateTime(present_time);
	if (present_day != TriggerFactory::getPresentDay())
	{
		TriggerFactory::setPresentDay(present_day);
		DeviceFactory::setSchedules();
		//writing records from a collection to a file
	}
	return;
}

void shutdown(Testees* test)
{
	delete test;

	RecordFactory::dumpRecords();

	RecordFactory::clear();
	DeviceFactory::clear();
}

int main()
{
	std::cout << "Hello World\n";
	srand(time(nullptr));
	//populating with test devices
	Testees::loadFile("animal_names.csv");
	Testees* test = new Testees();

	int rand_type;
	int capacity = (test->nleft > 10) ? test->nleft - 10 : 0;
	while (test->nleft > capacity)
	{
		rand_type = rand() % 2;
		DeviceFactory::makeDevice(rand_type, test->popName());
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
			option_num = -1;
		}
		if (option_num == 4)
		{
			std::cin >> menu_input;
		}
		updatetime();
		switch (option_num)
		{
		case -1:	//typed a device name, perform Oneclick
			system("cls");
			d_subject = DeviceFactory::getDevice(menu_input);
			if (d_subject.first != nullptr)
			{
				d_subject.first->OneClick();
			}
			else { std::cout << "Couldn't find a device by that name\n"; }
			break;
		case 1:
			system("cls");
			DeviceFactory::printDeviceList();
			break;
		case 2:
			system("cls");
			DeviceFactory::printDeviceByName();
			break;
		case 4:
			d_subject = DeviceFactory::getDevice(menu_input);
			if (d_subject.first != nullptr)
			{
				system("cls");
				CL_Menu::makeMenu(d_subject);
				menu = CL_Menu::get();
			}
			else { std::cout << "Couldn't find a device by that name\n"; }
			break;
		case 5:
			system("cls");
			CL_Menu::makeMenu(1,6);
			menu = CL_Menu::get();
			menu->PrintLine();
			menu->newDeviceMenu();

			CL_Menu::close();
			menu = CL_Menu::get();
			break;
		case 9:
			play = false;
			break;
		}
		//std::cout << "\n" << option_num << menu_input << "\n";
	}
	updatetime();
	shutdown(test);

	return 0;
}