#include "dxgraphics.h"
#include "game.h"
#include <map>
#include "Camera.h"
#include "trace.h"
#include "Scene1.h"
#define MAX_LOOKUP -70
#define MAX_LOOKDOWN 70


MyCamera* MyCamera::_instance = NULL;

MyCamera::MyCamera()
{
	_distanceUpDown = 0;
	_width = SCREEN_WIDTH/SCALE_RATE ;
	_height = SCREEN_HEIGHT/SCALE_RATE;
	_viewRect = RECT();
	_position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	_anchor = MIDDLE;
	CalAnchorPoint();
	_vx = 0;
	_vy = 0; 
}

void MyCamera::Update(float t)
{
	//_vx -= _vx*FRICTION;
	//_vy -= _vy*FRICTION;
	
	

	if (_isStop == false)
	{
		_position.x += (_vx)*t;

	}
	_position.y += _vy*t;



	if (_position.x < _width/2 )
	{
		_position.x = _width/2 ;
	}
	if (_position.x > _curMapWidth - _width / 2)
	{
		_position.x = _curMapWidth - _width / 2;
	}



	if (_position.y < _height / 2)
		_position.y = _height / 2;
	if (_position.y > _curMapHeight / 2 - _height / 2)
	{
		_position.y = _curMapHeight / 2 - _height / 2;
	}
	_viewRect.top = -_height / 2 + _position.y;

	_viewRect.bottom = _viewRect.top + _height;

	if (_position.x <= _width / 2)
	{
		_viewRect.left = 0;
		_viewRect.right = _width;
	}
	else
	{
		if (_position.x >= _curMapWidth - _width / 2)
		{
			_viewRect.right = _curMapWidth;
			_viewRect.left = _curMapWidth - _width;
		}
		else
		{
			_viewRect.left = _position.x - _width / 2;
			_viewRect.right = _position.x + _width / 2;
		}
	}

	_boundingBox = _viewRect;
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


RECT MyCamera::View()
{
	return _viewRect;
}

void MyCamera::LookUp(float t, bool toNormal)
{

	_vy = -0.15;

	if (((_distanceUpDown+_vy*t <= MAX_LOOKUP || _distanceUpDown+_vy*t >= MAX_LOOKDOWN) && toNormal == false) 
		|| _distanceUpDown + _vy*t <= (  _height / 2 - _position.y)
		|| (toNormal == true && int( _distanceUpDown) == 0))
	{
		_vy = 0;
	}
	 
	_distanceUpDown += _vy*t; 
}

//Update(0);


void MyCamera::LookDown(float t, bool toNormal)
{
	  
		_vy = 0.15;
		//trace(L"_distanceUpDown=%f cuMapHeight/2= %f  - _positionY = %f", _distanceUpDown, _curMapHeight / 2, _position.y);
		
		if (((_distanceUpDown+_vy*t <= MAX_LOOKUP || _distanceUpDown+_vy*t >= MAX_LOOKDOWN) && toNormal == false)
			 || _distanceUpDown+ _vy*t >= _curMapHeight / 2 - _height / 2 - _position.y
			|| (toNormal == true && int(_distanceUpDown) == 0))
		{
			_vy = 0;
		}

		_distanceUpDown += _vy*t;
		//trace(L"%f", _distanceUpDown);
	
}

