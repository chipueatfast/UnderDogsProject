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
#include "game.h"

#define CHARACTER_VX 10

using namespace std;
class AppleBullet : public GameObject
{
private:
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

	AppleBullet();
	AppleBullet(int x, int y, Face face);
};


class Aladdin : public GameObjectMove
{
	string _prev_main_state;
public:
	string prev_main_state() const
	{
		return _prev_main_state;
	}

	void set_prev_main_state(const string& cs)
	{
		_prev_main_state = cs;
	}

private:
	bool _onStateEnd;
public:
	bool on_state_end() const
	{
		return _onStateEnd;
	}

	void set_on_state_end(bool on_state_end)
	{
		_onStateEnd = on_state_end;
	}


private:
	
	list<AppleBullet*>* _bulletList;
	int _appleCount;
	CSound* _soundAppleEmty;
	CSound* _soundThrowApple;
	bool _isClimbing = false;
	int _chosenLayer = 0;

	int _randomIdle = 6;
	int _randomIdleCount = 0;
	Face _facePush;
	bool _isSetStatePush = false;
	bool _isWalkingStairs = false;

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
	bool _isAbsorbed;

public:
	bool is_absorbed() const
	{
		return _isAbsorbed;
	}

	void set_is_absorbed(bool is_absorbed)
	{
		_isAbsorbed = is_absorbed;
	}

	void set_ChosenLayer(const int & chosenlayer)
	{
		_chosenLayer = chosenlayer;
	}

	int ChosenLayer() const
	{
		return _chosenLayer;
	}

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
	string _degreeState;
public:
	string degree_state() const
	{
		return _degreeState;
	}

	void set_degree_state(const string& cs)
	{
		_degreeState = cs;
	}

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
	}

	void set_vy(float vy)
	{
		_vy = vy;
	}

	//Nam 12/3


	void Render(bool isRotation, bool isScale, bool isTranslation) override;

	bool isAllowChangeState(string newState)
	{
		if (newState == "000")
		{
			string curState = _stateManager->curState().getName();
			if (curState == "StartIdle2" || curState == "Idle2" || curState == "Idle3")
			{
				return false;
			}
		}
		return true;
	}
	void set_FacePush(GameObject::Face facePush)
	{
		_facePush = facePush;
	}
	void isSetStatePush(bool isUsePush)
	{
		_isSetStatePush = isUsePush;
	}
	void set_IsWalkingStairs(bool isWalking)
	{
		_isWalkingStairs = isWalking;
	}

private:
	int _score = 100;
	int _diamondCount = 4;
	int _life = 3;
	//mainCharacter->setPosition(MyCamera::GetInstance()->width() / 2, 600);
	D3DXVECTOR3 _positionCheckpoint = D3DXVECTOR3(SCREEN_WIDTH / 2, 600, 0);
public:
	void Back();


	void setScore(int newScore)
	{
		_score = newScore;
	}
	int Score()
	{
		return _score;
	}

	void setPositionCheckpoint(D3DXVECTOR3 newCheckpoint)
	{
		if (newCheckpoint.x <= _positionCheckpoint.x)
			return;
		_positionCheckpoint.x = newCheckpoint.x;
		_positionCheckpoint.y = newCheckpoint.y;
	}


	void setDiamondCount(int diamondCount)
	{
		_diamondCount = diamondCount;
	}
	int DiamondCount()
	{
		return _diamondCount;
	}

	int health()
	{
		return _health;
	}

	void set_health(int newHealth) override
	{
		if (newHealth < 0)
			return;
		_health = newHealth;
		if (_health == 0)
		{
			if (_life - 1 > 0)
			{
				_life -= 1;
				_health = 7;
				this->setPosition(_positionCheckpoint);
				MyCamera::GetInstance()->setPosition(_positionCheckpoint);
			}

		}
	}
	int Life()
	{

		return _life;
	}
	void setLife(int newLife)
	{
		if (newLife < 0)
		{
			return;
		}
		_life = newLife;

	}
};



#endif //  _ALADDIN_H_