#include "MyCamera.h"
#include "dxgraphics.h"
#include "game.h"
#include <map>

MyCamera* MyCamera::_instance = NULL;

MyCamera::MyCamera()
{
	_width = SCREEN_WIDTH;
	_height = SCREEN_HEIGHT;
	_viewRect = RECT();
	_position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	_vx = 0;
	_vy = 0;

}




void MyCamera::Update(float t)
{
	if (_isStop == false)
	{
		_position.x += _vx*t;
		_position.y += _vy*t;
	}

	_viewRect.top = (680 - SCREEN_HEIGHT)/* - (Global::GetHeight()/2 -position.y)*/;
	_viewRect.bottom = _viewRect.top + SCREEN_HEIGHT;
	if (_position.x <= SCREEN_WIDTH / 2)
	{
		_viewRect.left = 0;
		_viewRect.right = _width;
	}
	else
	{
		if (_position.x >= 1291 -SCREEN_WIDTH / 2)
		{
			_viewRect.right = 1291;
			_viewRect.left = 1291 - SCREEN_WIDTH;

		}
		else
		{
			_viewRect.left = _position.x - SCREEN_WIDTH / 2;
			_viewRect.right = _position.x + SCREEN_WIDTH / 2;
		}
	}
}


MyCamera::~MyCamera()
{
}

MyCamera * MyCamera::GetInstance()
{
	if (!_instance)
		_instance = new MyCamera();

	return _instance;
}

D3DXVECTOR3 MyCamera::Position()
{
	return _position;
}

RECT MyCamera::View()
{
	return _viewRect;
}

void MyCamera::LookUp()
{

}
