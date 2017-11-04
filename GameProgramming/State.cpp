#include "State.h"



State::State()
{ 
	_name = "";
}


State::~State()
{
}

State::State(const std::string stateName, const std::vector<RECT> rect)
{
	_name = stateName;
	_srcRect = rect;
}

std::vector<RECT> State::getListRect() const
{
	return _srcRect;
}


std::string State::getName() const
{
	return _name;
}