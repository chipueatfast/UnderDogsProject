#ifndef  _ALADDIN_H_
#define _ALADDIN_H_

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "StateManager.h"

using namespace std;


class Aladdin : public GameObject
{
private:
	int _health;
	StateManager _playerState;
	int _index;
	float _animadelay,_animaCount;
public:
	float animadelay() const
	{
		return _animadelay;
	}

	void set_animadelay(float animadelay)
	{
		_animadelay = animadelay;
	}

	Aladdin();
	~Aladdin();

	void Init();
	void Update(float t);
	void Render(D3DXVECTOR3* AnchorPoint) override ;

	void setState(string newState);
	void Move(int keycode);

	void Next();
	void Reset();
	void BeHitted();
};

#endif //  _ALADDIN_H_