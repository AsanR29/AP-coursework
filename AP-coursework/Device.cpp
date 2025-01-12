#include "Device.h"

Device::Device() : status(false) {};
Device::Device(std::string name) : _name(name), status(false) {};
Device::Device(std::string name, bool status) : _name(name), status(status) {};

std::string Device::getName()
{
	return _name;
}

void Device::updateDeviceName(std::string name)
{
	_name = name;
	return;
}

void Device::On()
{
	status = true;
}
void Device::Off()
{
	status = false;
}
void Device::OneClick()
{
	if (status) { Off(); }
	else { On(); }
}

void input_int(int& output)
{
	std::string dump;
	output = -1;
	std::cin >> output;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin >> dump;
	}
	//return output;
}
void input_int(int& output, std::string error_response)
{
	std::string dump;
	output = -1;
	std::cin >> output;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin >> dump;

		std::cout << error_response;
		std::cin >> output;
	}
	//return output;
}
void input_timeofday(int& output_hour, int& output_min, std::string error_response)
{
	std::string input;
	bool failure = false;

	int colon_index;
	output_hour = -1, output_min = -1;
	while (output_hour < 0 || 24 < output_hour || output_min < 0 || 59 < output_min)
	{
		if (failure) { std::cout << error_response; }
		failure = true;

		input_string(input);
		colon_index = input.find(":");
		try {
			output_hour = std::stoi(input.substr(0, colon_index));
		}
		catch (std::invalid_argument) { continue; }
		try {
			output_min = std::stoi(input.substr(colon_index + 1, input.size() - colon_index));
		}
		catch (std::invalid_argument) { continue; }
	}
	output_hour %= 24;
}
void input_int_inrange(int& output, int max_included)
{
	std::string dump;
	output = -1;
	std::cin >> output;
	while (std::cin.fail() || output < 0 || max_included < output)
	{
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin >> dump;
		}

		std::cout << "Input must be between 0 and " << max_included << "\n";
		std::cin >> output;
	}
	//return output;
}
void input_string(std::string& output)	//this is a replacement for getline() because getline messes everything else up
{
	output = "";
	std::string inp{ "" };
	bool space = false;
	while (std::cin >> inp)
	{
		if (space) { output += " "; }
		output += inp;
		space = true;
		inp = std::cin.peek();
		if (inp == "\n") { break; }
	}
	return;
}
