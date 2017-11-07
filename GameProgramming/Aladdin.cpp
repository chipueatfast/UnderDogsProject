#include "Aladdin.h"
#include "dxgraphics.h"
#include <dinput.h>
#include "game.h"
#include "Camera.h"


Aladdin::Aladdin()
{
	_index = 0;
	_animadelay = 2.0f;
	_animaCount = 0;
	_health = 7;
	_curface = Face::RIGHT;
	_lastface = _curface;
	_playerState = StateManager("Res\\AladdinSpriteXML.xml");
	this->setSprite(new Sprite("Res\\Aladdin.png", 40, 50));
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
		if (_playerState.curState().getName() == "IdleUp" || _playerState.curState().getName() == "IdleDown")
			Next2();
		else
			Next();
		_animaCount = 0;
		_width = _playerState.curState().getListRect().at(_index).right - _playerState.curState().getListRect().at(_index).left;
		_height = _playerState.curState().getListRect().at(_index).bottom - _playerState.curState().getListRect().at(_index).top;
		// update lai anchorpoint do frame co bounding khac nhau
		calAnchorPoint();


	}
	_lastface = _curface;

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

	if (_position.x < SCREEN_WIDTH / 2)
	{
		setTranslation(D3DXVECTOR2(_position.x, _position.y));
	}
	else
	{
		if (_position.x >= 4773 - SCREEN_WIDTH / 2)
		{
			setTranslation(D3DXVECTOR2(SCREEN_WIDTH - (-_position.x + 4773), _position.y));
		}
		else
		{
			if (_vx != 0)
				setTranslation(D3DXVECTOR2(SCREEN_WIDTH / 2, _position.y));
			else
			{
				int fix_range;
				if (_curface == Face::LEFT)
					fix_range = 40;
				else
				{
					fix_range = -40;
				}
				setTranslation(D3DXVECTOR2(SCREEN_WIDTH / 2 + fix_range, _position.y));
			}
		}
	}


}

void Aladdin::Render(AnchorPoint type, bool isRotation, bool isScale, bool isTranslation)
{
	//D3DXMATRIX oldmatrix;
	//sprite_handler->GetTransform(&oldmatrix);
	Transform(isRotation, isScale, isTranslation);

	sprite_handler->Draw(
		_sprite->image(),
		&_playerState.curState().getListRect().at(_index),
		&_anchorPoint,
		NULL,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	sprite_handler->SetTransform(&old_matrix);

}

void Aladdin::setState(string newState)
{
	if (_playerState.curState().getName() != newState)
	{
		_playerState.setState(newState);
		Reset();
	}

}


void Aladdin::Move(int keycode)
{
	switch (keycode)
	{
	case DIK_LEFT:
	{
		setState("Run");

		_curface = Face::LEFT;
		if (_lastface != _curface)
			Flip();

		Run();
	}; break;
	case DIK_RIGHT:
	{
		setState("Run");

		_curface = Face::RIGHT;
		if (_lastface != _curface)
			Flip();

		Run();
	}; break;
	}
}



void Aladdin::Next()
{
	int size = _playerState.curState().getListRect().size() - 1;
	if (size > 0)
		_index = (_index + 1) % size;
	else
		_index = 0;

}

void Aladdin::Next2()
{
	int size = _playerState.curState().getListRect().size() - 1;
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
	return _playerState.curState().getName();
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