#pragma once
#include "Device.h"
#include "RecordFactory.h"
#include "Schedule.h"

class Socket : public Device
{
private:
	double live_energy;
	Schedule schedule;

	void TakeEnergy();
	//void TakeSleepTimer();
public:
	Socket(std::string name);
	Schedule* GetSchedule();

	int TakeInput(int input);

	void updateEnergy(double);

	void PrintLine();
	std::string tagline();
};

