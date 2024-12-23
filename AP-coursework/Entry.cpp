#include <iostream>
#include "RecordFactory.h"
#include "DeviceFactory.h"
#include "Sensor.h"
#include "Testees.h"

int main()
{
#ifdef _DEBUG
	//_CrtSetBreakAlloc(165);
	_onexit(_CrtDumpMemoryLeaks);
#endif
	//start
	srand(time(nullptr));

	Testees::loadFile("animal_names.csv");
	Testees* test = new Testees();

	std::cout << "Hello World.\n";
	/*Sensor* test = new Sensor("test");
	test->PrintLine();
	C_record old_test = test->updateTemperature(15.6f);
	test->PrintLine();
	old_test.PrintLine();
	H_record humid_test = test->updateHumidity(88.17f);
	test->PrintLine();
	old_test.PrintLine();
	humid_test.PrintLine();*/

	while (test->nleft > 0)
	{
		DeviceFactory::makeDevice("sensor", test->popName());
	}

	//DeviceFactory::makeDevice("sensor", test->popName());
	//Device* happy = DeviceFactory::getDevice("Happy");
	//std::cout << "And its called... " << happy->getName() << "!\n";

	bool play = true;
	int menu_input;
	while (play)
	{
		std::cout << "Menu options\n1) List devices\n2)\n3)\n4)\n5) Quit\n>";
		std::cin >> menu_input;
		switch (menu_input)
		{
		case 1:
			DeviceFactory::printDeviceList();
		}
	}

	return 0;
}