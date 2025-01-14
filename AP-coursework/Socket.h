#pragma once
#include "Device.h"
#include "RecordFactory.h"
#include "Schedule.h"

/*
Not quite sure why a Socket would need both a Schedule and a Sleep Timer?
Do sockets even drain any power when theres nothing plugged in? 
I've programmed it as if you want it to turn off overnight, but turn on before you get up
To like charge your phone, I suppose.

Another assumption is that "live_energy" is being detected, and not dictated.
It should be detected as 0 when the Socket is forced off, so I will not program it to do that.
*/

class Socket : public Device
{
private:
	//data members
	double live_energy;
	Schedule schedule;

	//private input functions
	void TakeEnergy();
public:
	//constructors
	Socket(std::string name);
	
	//setters which create Data_records
	void updateEnergy(double);

	//used by CL_Menu to access private functions
	int TakeInput(int input);

	//used for command line output
	void PrintLine();
	std::string tagline();
	
	//public methods primarily for file input/output
	Schedule* GetSchedule();
	friend std::ofstream& operator<<(std::ofstream& ost, Socket& device);
	friend std::ifstream& operator>>(std::ifstream& ist, Socket& device);

	//destructor
	~Socket();
};

