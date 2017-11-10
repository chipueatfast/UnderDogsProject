#include "Aladdin.h"
#include "dxgraphics.h"
#include <dinput.h>
#include "game.h"
#include "Camera.h"
#include "trace.h"


Aladdin::Aladdin()
{
	_index = 0;
	_animadelay = 2.0f;
	_animaCount = 0;
	_health = 7;
	_curface = Face::RIGHT;
	_lastface = _curface;
	_mainState = "0";
	_subState = "0";
	_handState = "0";
	_playerState = new StateManager("Res\\AladdinSpriteXML.xml");
	this->setSprite(new Sprite("Res\\Aladdin.png", 40, 50));
	_playerState->AddToDictState("000", "Idle1");
	_playerState->AddToDictState("001", "IdleThrow");
	_playerState->AddToDictState("002", "IdleSlash");
	_playerState->AddToDictState("100", "Run");
	_playerState->AddToDictState("300", "IdleDown");
	_playerState->AddToDictState("200", "IdleUp");
	_playerState->AddToDictState("002", "IdleSlash");
	_playerState->AddToDictState("102", "RunSlash");
	_playerState->AddToDictState("202", "IdleUpSlash");
	_playerState->AddToDictState("302", "IdleDownSlash");
}


Aladdin::~Aladdin()
{
}

void Aladdin::Init()
{
}

void Aladdin::Update(float t)
{
	_animaCount += t;
	if (_animaCount >= _animadelay)
	{
		if (_playerState->curState().getName() == "IdleUp" || _playerState->curState().getName() == "IdleDown")
			Next2();
		else
			Next();
		_animaCount = 0;
		_width = _playerState->curState().getListRect().at(_index).right - _playerState->curState().getListRect().at(_index).left;
		_height = _playerState->curState().getListRect().at(_index).bottom - _playerState->curState().getListRect().at(_index).top;
		// update lai anchorpoint do frame co bounding khac nhau
		calAnchorPoint();
		this->player_state()->set_life_span(this->player_state()->life_span() - 1);
		if (this->player_state()->life_span() == 0)
		{
			this->set_hand_state("0");
		}


	}
	//_lastface = _curface;

	_position.x += _vx*t;
	_position.y += _vy*t;
	if (_position.x < 0)
	{
		_position.x = 0;
	}
	if (_position.x > 4773)
	{
		_position.x = 4773;
	}


	//float distance = MyCamera::GetInstance()->Position().x - _position.x;
	////if ((abs(distance) > SCREEN_WIDTH / 3 ))
	////{
	////	MyCamera::GetInstance()->Stop();
	////}
	//	if ((distance < SCREEN_WIDTH /3 && _vx < 0) || (distance > -SCREEN_WIDTH / 3 && _vx > 0)) // ktra nv co vuot qua range cua CAM ko 
	//		MyCamera::GetInstance()->Stop();

	//	if ((distance > 0 && distance < SCREEN_WIDTH / 3 && _vx > 0)
	//		|| (distance > -SCREEN_WIDTH / 3 && distance < 0 && _vx < 0))
	//	{
	//		MyCamera::GetInstance()->Move();
	//		trace(L"Distance : %.2f", distance);
	//	}
	//
	//	setTranslation(D3DXVECTOR2(SCREEN_WIDTH / 2 - distance, _position.y));
	
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
		&_playerState->curState().getListRect().at(_index),
		&_anchorPoint,
		NULL,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	sprite_handler->SetTransform(&old_matrix);

}

void Aladdin::setState(string newState)
{
	if (_playerState->curState().getName() != _playerState->dict_state()[newState])
	{
		_playerState->setState(newState);
		Reset();
	}

}




void Aladdin::Next()
{
	int size = _playerState->curState().getListRect().size() - 1;
	if (size > 0)
		_index = (_index + 1) % size;
	else
		_index = 0;

}

void Aladdin::Next2()
{
	int size = _playerState->curState().getListRect().size() - 1;
	if (_index < size)
		_index++;
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
	return _playerState->curState().getName();
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
