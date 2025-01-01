#pragma once
#include <iostream>
#include <string>
class Device
{
private:
protected:
	std::string _name;
	bool status;	//true=on, false=off

	void TakeDeviceName();
public:
	Device();
	Device(std::string);
	std::string getName();
	void updateDeviceName(std::string);

	virtual void PrintLine() = 0;
	virtual std::string tagline() = 0;
	virtual int TakeInput(int) = 0;
	//irtual void OneClick() = 0;
};

