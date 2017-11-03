#include "Aladdin.h"
#include "dxgraphics.h"


Aladdin::Aladdin()
{
	_index = 0;
	_animadelay = 2.0f;
	_animaCount = 0;
	_health = 7;
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
		_width = _playerState.curState().getListRect().at(_index).right- _playerState.curState().getListRect().at(_index).left;
		_height = _playerState.curState().getListRect().at(_index).bottom- _playerState.curState().getListRect().at(_index).top;
		switch(_anchor)
		{
		case BOTTOM_MID:
		{
			_anchorPoint = D3DXVECTOR3(_width/ 2, _height, 0);
		}; break;
		}
	}
}

void Aladdin::Render(D3DXVECTOR3* AnchorPoint)
{
	sprite_handler->Draw(
		_sprite->image(),
		&_playerState.curState().getListRect().at(_index),
		AnchorPoint,
		NULL,
		D3DCOLOR_XRGB(255, 255, 255)
	);

}

void Aladdin::setState(string newState)
{
	_playerState.setState(newState);

}


void Aladdin::Move(int keycode)
{
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
