#ifndef _STATE_MANAGER_H_
#define _STATE_MANAGER_H_
#include <map>
#include "State.h"
#include <vector>
using namespace std;

class StateManager
{
private:
	State _curState;
public:
	State curState() const
	{
		return _curState;
	}

private:
	//Sta	te_Name _state;
	map<string, State> _mapState;
	vector<string> _listStateName;

public:
	StateManager();
	~StateManager();
	StateManager(char* xmlpath);
	void setState(string targetState);
};

#endif // !_STATE_MANAGER_H_
