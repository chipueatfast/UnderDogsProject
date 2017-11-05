#include "Aladdin.h"
#include "dxgraphics.h"
#include <dinput.h>


Aladdin::Aladdin()
{
	_index = 0;
	_animadelay = 2.0f;
	_animaCount = 0;
	_health = 7;
	_curface = Face::RIGHT;
	_lastface = _curface;
	_playerState = StateManager("D:\\AladdinSpriteXML.xml");
	this->setSprite(new Sprite("Res\\Aladdin.png",40,50));
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
		Next();
		_animaCount = 0;
		_width = _playerState.curState().getListRect().at(_index).right - _playerState.curState().getListRect().at(_index).left;
		_height = _playerState.curState().getListRect().at(_index).bottom - _playerState.curState().getListRect().at(_index).top;
		// update lai anchorpoint do frame co bounding khac nhau
		calAnchorPoint();
	}

	_lastface = _curface;
}

void Aladdin::Render(AnchorPoint type, bool isRotation, bool isScale, bool isTranslation)
{
	Transform(isRotation, isScale, isTranslation);

		sprite_handler->Draw(
		_sprite->image(),
		&_playerState.curState().getListRect().at(_index),
		&_anchorPoint,
		NULL,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	sprite_handler->SetTransform(old_matrix);

}

void Aladdin::setState(string newState)
{
	_playerState.setState(newState);

}


void Aladdin::Move(int keycode)
{
	switch (keycode)
	{
	case DIK_LEFT:
	{
		if(CurrentState() != "Running")
			setState("Running");
		if (_lastface != _curface)
			Flip();
		_curface = Face::LEFT;
		Run();
	}; break;
	case DIK_RIGHT:
	{
		if (CurrentState() != "Running")
			setState("Running");
		if (_lastface != _curface)
			Flip();
		_curface = Face::RIGHT;
		Run();
	}; break;
	}
}



void Aladdin::Next()
{
	int size = _playerState.curState().getListRect().size() - 1;
	_index = (_index + 1)%size;

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
	if(_curface == Face::RIGHT)
	{
		_vx = CHARACTER_VX;
	}
	else
	{
		_vy = -CHARACTER_VX;
	}
}
