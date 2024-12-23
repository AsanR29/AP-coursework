#include "Testees.h"
//static member initialisations
bool Testees::initialised = false;
std::vector<std::string> Testees::s_names;

void Testees::loadFile(std::string file_name)
{
	if (Testees::initialised == true) { return; }
	std::ifstream ist(file_name);

	std::string n_string;
	if (ist.is_open())
	{
		while (ist >> n_string)
		{
			Testees::s_names.push_back(n_string);
		}
	}	
	Testees::initialised = true;
	return;
}

std::string Testees::getName()
{
	int rand_i = rand() % s_names.size();
	return s_names[rand_i];
}

Testees::Testees() : _names(Testees::s_names), nleft(s_names.size()) {};

std::string Testees::popName()
{
	std::string name;
	int rand_i = rand() % _names.size();
	name = _names[rand_i];
	_names.erase(_names.begin() + rand_i);
	--nleft;
	return name;
}