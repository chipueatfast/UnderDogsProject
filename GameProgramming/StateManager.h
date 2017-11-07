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
	int _lifeSpan;
public:
	int life_span() const
	{
		return _lifeSpan;
	}

	void set_life_span(int life_span)
	{
		_lifeSpan = life_span;
	}

	// used to check press state
	State curState() const
	{
		return _curState;
	}

private:
	//Sta	te_Name _state;

	map<string, string> _dictState;
public:
	map<string, string> dict_state() const
	{
		return _dictState;
	}

	void set_dict_state(const map<string, string>& pairs)
	{
		_dictState = pairs;
	}

private:
	map<string, State> _mapState;


public:
	StateManager();
	~StateManager();
	//Add an element to dictstate
	void AddToDictState(string key, string data);
	StateManager(char* xmlpath);
	void setState(string stateCode);
};

#endif // !_STATE_MANAGER_H_
