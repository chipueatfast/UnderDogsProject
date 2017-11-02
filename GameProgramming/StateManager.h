#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_

#include "PlayerState.h"

class StateManager
{
private:
	State_Name _curState;
	//Sta	te_Name _state;
public:
	StateManager(State_Name state);
	~StateManager();
	void setState(State_Name targetState);
};

#endif // !_STATE_MANAGER_H_
