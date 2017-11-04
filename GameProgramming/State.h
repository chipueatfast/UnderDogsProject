#pragma once
#include <string>
#include <Windows.h>
#include "pugixml.hpp"
#include <vector>
using namespace pugi;

class State
{
private:
	std::vector<RECT> _srcRect;
	std::string _name;
public:
	State();
	~State();
	State(std::string stateName,std::vector<RECT> rect);
	std::vector<RECT> getListRect() const;
	std::string	getName() const;
};