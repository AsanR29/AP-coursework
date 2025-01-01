#pragma once
#include <iostream>
#include <fstream>
#include <vector>
class Testees
{
private:
	//static
	static bool initialised;	//this is false
	static std::vector<std::string> s_names;

	//non-static
	std::vector<std::string> _names;
public:
	//static
	void static loadFile(std::string file_name);
	static std::string getName();

	//non-static
	Testees();
	std::string popName();
	int nleft;
	~Testees();
	void static clear();
};