#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

#include "StateData.h"
enum State_Name
{
	STANDING,
	RUNNING,
	JUMPING
};

class PlayerState
{
protected:
	StateData _data;
public:
	PlayerState();
	~PlayerState();
	virtual void Update() = 0;
	virtual void state() = 0;
	void setData(int state, LPWSTR filepath);
	StateData data();

};
#endif // !_PLAYER_STATE_H_
