#include "StateManager.h"
#include "Transition_check.h"



StateManager::StateManager(State_Name state)
{
	_curState = state;
}


StateManager::~StateManager()
{
}

void StateManager::setState(State_Name targetState)
{
	if (checker(_curState, targetState) == true)
	{
		_curState = targetState;
	}
}
