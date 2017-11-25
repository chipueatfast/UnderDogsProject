#ifndef  _ALADDIN_H_
#define _ALADDIN_H_

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "StateManager.h"
#include "Camera.h"
#include <list>
#include "dxaudio.h"
#include "GameObjectMove.h"

#define CHARACTER_VX 20

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


class Aladdin : public GameObjectMove
{


private:
	
	list<AppleBullet*>* _bulletList;
	int _appleCount;
	CSound* _soundAppleEmty;
	CSound* _soundThrowApple;
	bool _isClimbing = false;
public:
	int appleCount() const
	{
		return _appleCount;
	}

	void setAppleCount(int appleCount)
	{
		_appleCount = appleCount;
	}

	list<AppleBullet*>* bullet_list() const
	{
		return _bulletList;
	}

	void set_bullet_list(list<AppleBullet*>* apple_bullets)
	{
		_bulletList = apple_bullets;
	}

	

private:
	int _health;
	int _invicibleTime;
//to edit later
	bool _isSwinging = false;

public:
	bool isSwinging() const
	{
		return _isSwinging;
	}

	void setIsSwinging(bool is_swinging)
	{
		_isSwinging = is_swinging;
	}

private:
	CSound* _soundAladdinBeBeaten;
public:
	Aladdin();
	~Aladdin();

	RECT NextBounding();
	 

	bool isClimbing() const
	{
		return _isClimbing;
	}

	void setIsClimbing(bool isClimbing)
	{
		_isClimbing = isClimbing;
	}
	void FireApple();

	void Init();
	void PhysicUpdate(float t) override;
	void GraphicUpdate(float t) override;
	//void Render(bool isRotation = false, bool isScale = false, bool isTranslation = true);
	void DrawBullet();

	void setState(string newState);

	void Reset();
	void BeBeaten();
	string CurrentState();

	void Run();
	void StopX() { _vx = 0; };
	void StopY() { _vy = 0; };


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