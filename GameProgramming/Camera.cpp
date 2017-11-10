#include "dxgraphics.h"
#include "game.h"
#include <map>
#include "Camera.h"
#include "trace.h"

MyCamera* MyCamera::_instance = NULL;

MyCamera::MyCamera()
{
	_width = SCREEN_WIDTH;
	_height = SCREEN_HEIGHT;
	_viewRect = RECT();
	_position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	_vx = 0;
	_vy = 0;
	_additonDis = 0;

}




void MyCamera::Update(float t)
{
	//_vx -= _vx*FRICTION;

	if (_isStop == false)
	{
		_position.x += (_vx)*t;
		_position.y += _vy*t;
		//trace(L"\n\nAddition : %.2f", _additonDis);
		//trace(L"pos : %.2f", _position.x);
	}

	if (_position.x < SCREEN_WIDTH / 2)
	{
		_position.x = SCREEN_WIDTH / 2;
	}
	if (_position.x > 4773 - SCREEN_WIDTH / 2)
	{
		_position.x = 4773 - SCREEN_WIDTH / 2;
	}

	_viewRect.top = (_curMapHeight / 2 - SCREEN_HEIGHT)/* - (Global::GetHeight()/2 -position.y)*/;
	_viewRect.bottom = _viewRect.top + SCREEN_HEIGHT;
	if (_position.x <= SCREEN_WIDTH / 2)
	{
		_viewRect.left = 0;
		_viewRect.right = _width;
	}
	else
	{
		if (_position.x >= _curMapWidth - SCREEN_WIDTH / 2)
		{
			_viewRect.right = _curMapWidth;
			_viewRect.left = _curMapWidth - SCREEN_WIDTH;
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