#pragma once
#include "Device.h"
#include "RecordFactory.h"

class Socket : public Device
{
private:
	double live_energy;

	void TakeEnergy();
	void TakeSleepTimer();
public:
	Socket(std::string name);

	int TakeInput(int input);

	void updateEnergy(double);

	void PrintLine();
	std::string tagline();
};

