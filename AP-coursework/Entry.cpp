#include <iostream>
#include "T_record.h"
#include "Sensor.h"

int main()
{
	std::cout << "Hello World.\n";
	Sensor* test = new Sensor("test");
	test->PrintLine();
	T_record old_test = test->updateData(15.6f);
	test->PrintLine();
	old_test.PrintLine();
	old_test = test->updateData(88.17f);
	test->PrintLine();
	old_test.PrintLine();

	return 0;
}