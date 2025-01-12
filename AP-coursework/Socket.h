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
	Socket(std::string name, bool status, double energy);
	Schedule* GetSchedule();

	int TakeInput(int input);

	void updateEnergy(double);

	void PrintLine();
	std::string tagline();
	
	friend std::ofstream& operator<<(std::ofstream& ost, Socket& device);
	friend std::ifstream& operator>>(std::ifstream& ist, Socket& device);
};

