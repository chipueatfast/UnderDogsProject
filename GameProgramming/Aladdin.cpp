#include "Aladdin.h"
#include "dxgraphics.h"
#include <dinput.h>
#include "game.h"
#include "Camera.h"
#include "trace.h"
#include "GameManager.h"
#include "dxinput.h"
#define BULLET_VX 30
#define BULLET_VY 3



Aladdin::Aladdin()
{
	_index = 0;
	_animaDelay = 1.0f;
	_animaCount = 0;
	_health = 7;
	_invicibleTime = 10;
	_curFace = Face::RIGHT;
	_lastFace = _curFace;
	_mainState = "0";
	_subState = "0";
	_handState = "0";
	_sword = new RECT();
	_stateManager = new StateManager("Res\\AladdinXML.xml");
	this->setSprite(new Sprite("Res\\Aladdin.png", 40, 50));
	_stateManager->AddToDictState("010", "IdleFall");
	_stateManager->AddToDictState("110", "RunFall");
	_stateManager->AddToDictState("020", "IdleJump");
	_stateManager->AddToDictState("120", "RunJump");
	_stateManager->AddToDictState("101", "RunThrow");
	_stateManager->AddToDictState("000", "Idle1");
	_stateManager->AddToDictState("001", "IdleThrow");
	_stateManager->AddToDictState("002", "IdleSlash");
	_stateManager->AddToDictState("100", "Run");
	_stateManager->AddToDictState("300", "IdleDown");
	_stateManager->AddToDictState("200", "IdleUp");
	_stateManager->AddToDictState("002", "IdleSlash");
	_stateManager->AddToDictState("102", "RunSlash");
	_stateManager->AddToDictState("202", "IdleUpSlash");
	_stateManager->AddToDictState("302", "IdleDownSlash");
	_stateManager->AddToDictState("022", "RunSlash");
	_stateManager->AddToDictState("012", "RunSlash");
	_stateManager->AddToDictState("122", "RunSlash");
	_stateManager->AddToDictState("112", "RunSlash");
	_stateManager->AddToDictState("301", "IdleDownThrow");
	_stateManager->AddToDictState("130", "Push");
	_stateManager->AddToDictState("400", "Climb");
	_stateManager->AddToDictState("420", "ClimbJump");
	_stateManager->AddToDictState("050", "SwingIdle");
	_stateManager->AddToDictState("250", "SwingIdle");
	_stateManager->AddToDictState("450", "SwingIdle");
	_stateManager->AddToDictState("550", "SwingIdle");
	_stateManager->AddToDictState("150", "Swing");
	_stateManager->AddToDictState("052", "SwingSlash");
	_stateManager->AddToDictState("051", "SwingThrow");
	_stateManager->AddToDictState("402", "SwingSlash");
	_stateManager->AddToDictState("401", "SwingThrow");
	_stateManager->AddToDictState("060", "Spin");
	_stateManager->AddToDictState("500", "Beaten");

	_bulletList = new list<AppleBullet*>();

	_appleCount = 10;
	_soundAladdinBeBeaten = LoadSound("Res/Audio/AladdinHitted.wave");
	_soundAppleEmty = LoadSound("Res/Audio/AppleThrowEmty.wave");
	_soundThrowApple = LoadSound("Res/Audio/AppleThrow.wave");
}


Aladdin::~Aladdin()
{
}

RECT Aladdin::NextBounding()
{
	return RECT();
}

void Aladdin::FireApple()
{

	OutputDebugString("\n");
	OutputDebugString(std::to_string(_appleCount).c_str());
	if (_appleCount > 0)
	{
		AppleBullet* temp = new AppleBullet(x(), y(), curface());
		D3DXVECTOR3 newPos;
		if (curface() == Face::RIGHT)
			newPos = this->CalPositon(TOP_RIGHT);
		else
		{
			newPos = this->CalPositon(TOP_LEFT);

		}
		temp->setPosition(newPos.x, newPos.y);
		_bulletList->push_back(temp);
		_soundThrowApple->Play();
		_appleCount--;
	}
	else
	{
		_soundAppleEmty->Play();
	}

}

void Aladdin::Init()
{
}

void Aladdin::PhysicUpdate(float t)
{
	if (this->vx() != 0)
	{
		if (this->vx() > 0)
		{
			this->set_curFace(GameObject::Face::RIGHT);
			MyCamera::GetInstance()->set_curFace(GameObject::Face::RIGHT);
		}
		else
		{
			this->set_curFace(GameObject::Face::LEFT);
			MyCamera::GetInstance()->set_curFace(GameObject::Face::LEFT);

		}
		if (this->CheckFlip())
			this->Flip();
	}


	GameObjectMove::PhysicUpdate(t);
	setPosition(x() + _vx*t, y() + _vy*t);

	if (_position.x < 0)
	{
		_position.x = _width;
	}
	if (_position.x > MyCamera::GetInstance()->curMapWidth())
	{
		_position.x = MyCamera::GetInstance()->curMapWidth() - _width;
	}
	if (_position.y < 0)
	{
		_position.y = _height;
	}
	if (_position.y > MyCamera::GetInstance()->curMapHeight() / 2)
	{
		_position.y = MyCamera::GetInstance()->curMapHeight() / 2 - _height;
	}


	for (list<AppleBullet*>::iterator i = _bulletList->begin(); i != _bulletList->end(); i++)
	{
		AppleBullet* temp_obj = *i;
		temp_obj->set_vy(temp_obj->vy()*1.1f);
		temp_obj->setPosition(temp_obj->x() + temp_obj->vx()*t, temp_obj->y() + temp_obj->vy()*t);
	}

	

}



void Aladdin::GraphicUpdate(float t)
{
	_animaCount++;

	if (_animaCount >= _animaDelay)
	{
		if (_stateManager->curState().getName() == "IdleUp" || _stateManager->curState().getName() == "IdleDown" || _stateManager->curState().getName() == "IdleJump" || _stateManager->curState().getName() == "IdleFall")
		{
			Next2();
			if (_index == _stateManager->curState().getListRect().size() - 1)
			{
				if (_stateManager->curState().getName() == "IdleUp")
				{
					MyCamera::GetInstance()->LookUp(t, false);
				}
				else
				{
					if (_stateManager->curState().getName() == "IdleDown")
					{
						MyCamera::GetInstance()->LookDown(t, false);
					}
					else
					{
						MyCamera::GetInstance()->UpDownToNormal(t);
					}
				}
			}
		}
		else
		{
			MyCamera::GetInstance()->UpDownToNormal(t);
			Next();
		}
		if ((_position.y < MyCamera::GetInstance()->getUpperHeight() || _position.y> MyCamera::GetInstance()->getLowerHeight())
			&& _boundingBox.top >= 0
			)
		{
			MyCamera::GetInstance()->setVy(this->vy());
		}
		else
			MyCamera::GetInstance()->setVy(0);
 

		_width = _stateManager->curState().getListRect().at(_index).right - _stateManager->curState().getListRect().at(_index).left;
		_height = _stateManager->curState().getListRect().at(_index).bottom - _stateManager->curState().getListRect().at(_index).top;

		_animaCount = 0;
		// update lai anchorpoint do frame co bounding khac nhau
		CalAnchorPoint();
		this->state_manager()->set_life_span(this->state_manager()->life_span() - 1);
		if (this->state_manager()->life_span() == 0)
		{
			this->set_hand_state("0");
		}
	}
	

	MyCamera::GetInstance()->setVy(_vy);
	//Set Camera LeftRight
	OutputDebugString(to_string(this->x()).c_str());
	MyCamera::GetInstance()->setVx(_vx);
	//if (this->x() > MyCamera::GetInstance()->getMaxLookRight() * 2
	//	&& this->x()  < MyCamera::GetInstance()->getCurMapWidth() - MyCamera::GetInstance()->getMaxLookRight() * 2
	//	)
	//{
	//	if (_vx > 0)
	//	{
	//		MyCamera::GetInstance()->LookLeft(t, false);
	//	}

	//	if (_vx == 0)
	//	{
	//		MyCamera::GetInstance()->LeftRightToNormal(t);
	//	}

	//	if (_vx < 0)
	//	{
	//		MyCamera::GetInstance()->LookRight(t, false);
	//	}

	//	MyCamera::GetInstance()->setVx(this->vx());

	//	if (((this->x() < MyCamera::GetInstance()->getMaxLookRight() * 3))
	//		|| ((this->x() > MyCamera::GetInstance()->getCurMapWidth() - MyCamera::GetInstance()->getMaxLookRight() * 3))
	//		)
	//	{
	//		MyCamera::GetInstance()->setVx(0);
	//		MyCamera::GetInstance()->setVxTranslate(0);
	//	} 
	//}
	//else
	//{
	//	MyCamera::GetInstance()->setDistanceLeftRight(0);
	//	MyCamera::GetInstance()->setVx(0);
	//	MyCamera::GetInstance()->setVxTranslate(0);
	//}


}



void Aladdin::DrawBullet()
{
	for (list<AppleBullet*>::iterator i = _bulletList->begin(); i != _bulletList->end(); i++)
	{
		AppleBullet* temp_obj = *i;
		temp_obj->setTranslation(D3DXVECTOR2(temp_obj->x() - MyCamera::GetInstance()->View().left, temp_obj->y() - MyCamera::MyCamera::GetInstance()->View().top));
		temp_obj->UpdateAnimate();
		temp_obj->Render();
	}
}

void Aladdin::setState(string newState)
{
	if (_stateManager->dict_state()[newState] == "")
		return;
	if (_stateManager->curState().getName() != _stateManager->dict_state()[newState])
	{
		Reset();
		_stateManager->setState(newState);

	}


}





void Aladdin::Reset()
{
	_index = 0;
}

void Aladdin::BeBeaten()
{
	_invicibleTime--;
	//OutputDebugString((std::to_string(_invicibleTime)).c_str());

	if (_invicibleTime == 0)
	{
		set_health(_health - 1);

		_soundAladdinBeBeaten->Play();
		_invicibleTime = 10;
	}


}

string Aladdin::CurrentState()
{
	return _stateManager->curState().getName();
}




AppleBullet::AppleBullet(int x, int y, Face face)
{

	_isPopping = false;
	if (face == Face::RIGHT)
		_vx = BULLET_VX;
	else
		_vx = -BULLET_VX;
	_vy = BULLET_VY;
	_isRepeating = false;
	this->setAnchor(TOP_LEFT);
	this->setPosition(x, y);
	this->setSprite(new Sprite("Res\\Aladdin.png", 7, 6));
	this->set_state_manager(new StateManager("Res\\AppleBullet.xml"));
	this->state_manager()->AddToDictState("000", "flying");
	this->state_manager()->AddToDictState("001", "popping");
	this->state_manager()->setState("000");

}

