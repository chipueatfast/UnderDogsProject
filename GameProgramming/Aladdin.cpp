#include "Aladdin.h"
#include "dxgraphics.h"
#include <dinput.h>
#include "game.h"
#include "Camera.h"
#include "trace.h"
#include "GameManager.h"
#define BULLET_VX 30.0f
#define BULLET_VY 3.0f



Aladdin::Aladdin()
{
	_index = 0;
	_animadelay = 2.0f;
	_animaCount = 0;
	_health = 7;
	_curface = Face::RIGHT;
	_lastface = _curface;
	_sword = new RECT();
	_mainState = "0";
	_subState = "0";
	_handState = "0";
	_stateManager = new StateManager("Res\\AladdinSpriteXML.xml");
	this->setSprite(new Sprite("Res\\Aladdin.png", 40, 50));
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
	_stateManager->AddToDictState("301", "IdleDownThrow");
	_stateManager->AddToDictState("130", "Push");
	_bulletList = new list<AppleBullet*>();
}


Aladdin::~Aladdin()
{
}

void Aladdin::FireApple()
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

}

void Aladdin::Init()
{
}

void Aladdin::PhysicUpdate(float t)
{
	setPosition(x() + _vx*t, y() + _vy*t);
	if (_position.x < 0)
	{
		_position.x = 0;
	}
	if (_position.x > 4773)
	{
		_position.x = 4773;
	}

	for (list<AppleBullet*>::iterator i = _bulletList->begin(); i != _bulletList->end(); i++)
	{
		AppleBullet* temp_obj = *i;
		temp_obj->set_vy(temp_obj->vy()*1.3f);
		temp_obj->setPosition(temp_obj->x() + temp_obj->vx(), temp_obj->y() + temp_obj->vy());
	}

	if (_handState == "2")
	{
		CalSword();
		if (_stateManager->life_span() == 0)
		{
			_handState = "0";
			DelSword();
		}
	}
}


void Aladdin::GraphicUpdate(float t)
{
	_animaCount += t;
	if (_animaCount >= _animadelay)
	{
		if (_stateManager->curState().getName() == "IdleUp" || _stateManager->curState().getName() == "IdleDown")
			Next2();
		else
			Next();
		_animaCount = 0;
		// update lai anchorpoint do frame co bounding khac nhau
		CalAnchorPoint();
		this->state_manager()->set_life_span(this->state_manager()->life_span() - 1);
		if (this->state_manager()->life_span() == 0)
		{
			this->set_hand_state("0");
		}


	}
	//_lastface = _curface;
	
	if (_position.x < SCREEN_WIDTH / 2)
	{
		setTranslation(D3DXVECTOR2(_position.x - MyCamera::GetInstance()->View().left, _position.y - MyCamera::GetInstance()->View().top));
		MyCamera::GetInstance()->Stop();
	}
	else
	{
		if (_position.x > 4773 - SCREEN_WIDTH / 2)
		{
			setTranslation(D3DXVECTOR2(_position.x - MyCamera::GetInstance()->View().left/*SCREEN_WIDTH - (-_position.x + 4773)*/, _position.y - MyCamera::GetInstance()->View().top));
			MyCamera::GetInstance()->Stop();
		}
		else
		{
			//if (_vx != 0)
			MyCamera::GetInstance()->Move();
				setTranslation(D3DXVECTOR2(_position.x - MyCamera::GetInstance()->View().left, _position.y - MyCamera::GetInstance()->View().top));
			/*else
			{
				int fix_range;	
				if (_curface == Face::LEFT)
					fix_range = 40;
				else
				{
					fix_range = -40;
				}
				setTranslation(D3DXVECTOR2(SCREEN_WIDTH / 2 + fix_range, _position.y));
			}*/
		}
	}
}

void Aladdin::Render(bool isRotation, bool isScale, bool isTranslation)
{
	//D3DXMATRIX oldmatrix;
	//sprite_handler->GetTransform(&oldmatrix);
	Transform(isRotation, isScale, isTranslation);

	sprite_handler->Draw(
		_sprite->image(),
		&_stateManager->curState().getListRect().at(_index),
		&_anchorPoint,
		NULL,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	sprite_handler->SetTransform(&old_matrix);

}

void Aladdin::DrawBullet(float deltaTime)
{
	for (list<AppleBullet*>::iterator i = _bulletList->begin(); i!=_bulletList->end(); i++)
	{
		AppleBullet* temp_obj = *i;
		temp_obj->setTranslation(D3DXVECTOR2(temp_obj->x() - MyCamera::GetInstance()->View().left,temp_obj->y() - MyCamera::GetInstance()->View().top));
		temp_obj->UpdateAnimate(false, deltaTime);
		temp_obj->Render();
	}
}

void Aladdin::setState(string newState)
{
	if (_stateManager->curState().getName() != _stateManager->dict_state()[newState])
	{
		_stateManager->setState(newState);
		
		Reset();
	}
	_width = _stateManager->curState().getListRect().at(_index).right - _stateManager->curState().getListRect().at(_index).left;
	_height = _stateManager->curState().getListRect().at(_index).bottom - _stateManager->curState().getListRect().at(_index).top;

}





void Aladdin::Reset()
{
	_index = 0;
}

void Aladdin::BeHitted()
{
}

string Aladdin::CurrentState()
{
	return _stateManager->curState().getName();
}



void Aladdin::Run()
{
	if (_curface == Face::RIGHT)
	{
		_vx = CHARACTER_VX;
	}
	else
	{
		_vx = -CHARACTER_VX;
	}
}

AppleBullet::AppleBullet(int x, int y, Face face)
{
	_isPopping = false;
	if (face == Face::RIGHT)
		_vx = BULLET_VX;
	else
		_vx = -BULLET_VX;
	_vy = BULLET_VY;
	this->setAnchor(TOP_LEFT);
	this->setPosition(x, y);
	this->setSprite(new Sprite("Res\\Aladdin.png", 7, 6));
	this->set_state_manager(new StateManager("Res\\AppleBullet.xml"));
	this->state_manager()->AddToDictState("000", "flying");
	this->state_manager()->AddToDictState("001", "popping");
	this->state_manager()->setState("000");

}

void Aladdin::CalSword()
{

	if (main_state() == "2")
	{
		_sword = &GetBoundingBox(main_state() + sub_state() + "2");
		return;
	}
	RECT temp_rect1 = GetBoundingBox(main_state() + sub_state() + "2");
	RECT temp_rect2 = GetBoundingBox(main_state() + sub_state() + "0");
	_sword->top = _boundingBox.top;
	_sword->bottom = _boundingBox.bottom;
	if (curface()==Face::RIGHT)
	{
		_sword->left = temp_rect2.right;
		_sword->right = temp_rect1.right;
		return;
	}
	else 
	{
		_sword->left = temp_rect1.left;
		_sword->right = temp_rect2.left;
		return;
	}

}

void Aladdin::DelSword()
{
	_sword->bottom = 0;
	_sword->top = 0;
	_sword->right = 0;
	_sword->left = 0;
}

