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
	bool _isLookRight = true;
public:
	Aladdin();
	~Aladdin();

	void Init();
	void Update(float t);
	void Render(AnchorPoint type = AnchorPoint::MIDDLE, bool isRotation = false, bool isScale = false, bool isTranslation = true) override ;

	void setState(string newState);
	void Move(int keycode);

	void Next();
	void Reset();
	void BeHitted();

	bool isLookRight() const
	{
		return _isLookRight;
	}

	void setIsLookRight(bool isLookRight)
	{
		_isLookRight = isLookRight;
	}

};

#endif //  _ALADDIN_H_