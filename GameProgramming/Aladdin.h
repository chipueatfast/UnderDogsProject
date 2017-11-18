#ifndef  _ALADDIN_H_
#define _ALADDIN_H_

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "StateManager.h"
#include "Camera.h"
#include <list>
#include "dxaudio.h"

#define CHARACTER_VX 0.2f

using namespace std;
class AppleBullet : public GameObject
{
	bool _isPopping;
public:
	bool is_popping() const
	{
		return _isPopping;
	}

	void set_is_popping(bool is_popping)
	{
		_isPopping = is_popping;
	}

	AppleBullet(int x, int y, Face face);
};


class Aladdin : public GameObject
{
private:
	RECT* _sword;
public:
	RECT* sword() const
	{
		return _sword;
	}

	void set_sword(RECT* tag_rect)
	{
		_sword = tag_rect;
	}
	void CalSword();
	void DelSword();

private:
	string _mainState, _subState, _handState;
	list<AppleBullet*>* _bulletList;
public:
	list<AppleBullet*>* bullet_list() const
	{
		return _bulletList;
	}

	void set_bullet_list(list<AppleBullet*>* apple_bullets)
	{
		_bulletList = apple_bullets;
	}

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
	int _invicibleTime;

	CSound* _soundAladdinBeHitted;
public:
	Aladdin();
	~Aladdin();

	void FireApple();

	void Init();
	void PhysicUpdate(float t);
	void GraphicUpdate(float t);
	//void Render(bool isRotation = false, bool isScale = false, bool isTranslation = true);
	void DrawBullet();

	void setState(string newState);

	void Reset();
	void BeHitted();
	string CurrentState();

	void Run();
	void Stop() { _vx = 0; };

	bool isLookRight() const
	{
		if (_curFace== Face::RIGHT)
			return true;
		return false;
	}
	void set_vx(float vx)
	{
		_vx = vx;
		MyCamera::GetInstance()->setVx(vx);
	}

	void set_vy(float vy)
	{
		_vy = vy;
		MyCamera::GetInstance()->setVy(vy);
	}
};



#endif //  _ALADDIN_H_