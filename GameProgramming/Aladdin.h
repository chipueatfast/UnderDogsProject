#ifndef  _ALADDIN_H_
#define _ALADDIN_H_

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "StateManager.h"

#define CHARACTER_VX 25

using namespace std;


class Aladdin : public GameObject
{
private:
	int _health;
	StateManager _playerState;
	int _index;
	float _animadelay, _animaCount;
	enum Face
	{
		LEFT,
		RIGHT
	} _curface, _lastface;
public:
	Aladdin();
	~Aladdin();

	void Init();
	void Update(float t);
	void Render(AnchorPoint type = AnchorPoint::MIDDLE, bool isRotation = false, bool isScale = false, bool isTranslation = true) override;

	void setState(string newState);
	void Move(int keycode);

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