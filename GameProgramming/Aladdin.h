#ifndef  _ALADDIN_H_
#define _ALADDIN_H_

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "StateManager.h"

#define CHARACTER_VX 0.2f

using namespace std;


class Aladdin : public GameObject
{
private:
	string _mainState, _subState, _handState;
public:
	string hand_state() const
	{
		return _handState;
	}

	void set_hand_state(const string& cs)
	{
		_handState = cs;
	}

	string main_state() const
	{
		return _mainState;
	}

	void set_main_state(const string& cs)
	{
		_mainState = cs;
	}

	string sub_state() const
	{
		return _subState;
	}

	void set_sub_state(const string& cs)
	{
		_subState = cs;
	}

private:
	int _health;
	StateManager* _playerState;
public:
	StateManager* player_state() const
	{
		return _playerState;
	}

	void set_player_state(StateManager* state_manager)
	{
		_playerState = state_manager;
	}

private:
	int _index;
	float _animadelay, _animaCount;
	
public:
	Aladdin();
	~Aladdin();

	void Init();
	void PhysicUpdate(float t);
	void GraphicUpdate(float t);
	void Render(bool isRotation = false, bool isScale = false, bool isTranslation = true);

	void setState(string newState);

	void Next();
	void Next2(); // ko rs _index;
	void Reset();
	void BeHitted();
	string CurrentState();

	void Run();
	void Stop() { _vx = 0; };

	bool isLookRight() const
	{
		if (_curface == Face::RIGHT)
			return true;
		return false;
	}

};

#endif //  _ALADDIN_H_