#include "PlayerState.h"



PlayerState::PlayerState()
{
}


PlayerState::~PlayerState()
{
}

void PlayerState::setData(int state, LPWSTR filepath)
{
	_data = StateData(state, filepath);
}


StateData PlayerState::data()
{
	return _data;
}
