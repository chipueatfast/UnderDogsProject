#pragma once
#include <string>
#include <Windows.h>
#include "pugixml.hpp"
using namespace pugi;

class StateRaw
{
private:
	RECT* _positions;
	int _countPositions;
	std::string _name;
public:
	StateRaw();
	~StateRaw();  
	StateRaw(char *path, std::string stateName);
	RECT* getPositions() const;
	int getCountPos() const;
	std::string	getName() const;
};

