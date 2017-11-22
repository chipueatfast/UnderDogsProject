#include "dxgraphics.h"
#include "game.h"
#include <map>
#include "Camera.h"
#include "trace.h"
#include "Scene1.h"
#define MAX_LOOKUP -_height/2
#define MAX_LOOKDOWN _height/2

#define MAX_LOOKLEFT - SCREEN_WIDTH/(6*SCALE_RATE)
#define MAX_LOOKRIGHT SCREEN_WIDTH/(6*SCALE_RATE)
#define MAX_LOOKMID _width/2


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
	_boundingBox = ExtraView();
}

void MyCamera::Update(float t)
{
	//_vx -= _vx*FRICTION;
	//_vy -= _vy*FRICTION;
	
	_distanceLeftRight += _vxTranslate*t;

	if (_isStopX == false)
	{
		_position.x += (_vx)*t;

	}
	if (_isStopY == false)
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

	_boundingBox = ExtraView();
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
RECT MyCamera::ExtraView()
{
	RECT extraView;
	extraView.top = _viewRect.top - BODER_SIZE;
	extraView.right = _viewRect.right + BODER_SIZE;
	extraView.left = _viewRect.left - BODER_SIZE;
	extraView.bottom = _viewRect.bottom + BODER_SIZE;


	return extraView;
}

void MyCamera::LookUp(float t, bool toNormal)
{

	_vy = -15;

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
	  
		_vy = 15;
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

#pragma region LEFTRIGHT 

void MyCamera::set_curFace(GameObject::Face face, int mainCharacter_x, int mainCharacter_y)
{
	if (face != this->_curFace)
	{
		_curFace = face;
		switch (face)
		{
		case Face::LEFT:

			break;
		case Face::RIGHT:

			break;
		}
	}
}


void MyCamera::LookLeft(float t, bool toNormal)
{
	_vxTranslate = -CHARACTER_VX;

	if (((_distanceLeftRight + _vxTranslate*t <= MAX_LOOKLEFT
		|| _distanceLeftRight + _vxTranslate*t >= MAX_LOOKRIGHT)
		&& toNormal == false)
		|| (toNormal == true && int(_distanceLeftRight) == 0))
	{
		_vxTranslate = 0;
	}


}

void MyCamera::LookRight(float t, bool toNormal)
{
	_vxTranslate = CHARACTER_VX;

	if (((_distanceLeftRight + _vxTranslate*t <= MAX_LOOKLEFT || _distanceLeftRight + _vxTranslate*t >= MAX_LOOKRIGHT) && toNormal == false) //khi vuot qua vi tri toi da
																																			 //|| _distanceLeftRight + _vxTranslate*t >= _curMapWidth / 2 - _width / 2 - _position.x
		|| (toNormal == true && int(_distanceLeftRight) == 0)) // khi dang muon tro ve vi tri can bang va da dat duoc vi tri can bang
	{
		_vxTranslate = 0;
	}
	//_distanceLeftRight += _vxTranslate*t;
	//trace(L"%f", _distanceLeftRight); 
}


void MyCamera::LeftRightToNormal(float t)
{
	_vxTranslate = 0;
	if (_distanceLeftRight > 0)
	{
		LookLeft(t, true);
	}
	if (_distanceLeftRight < 0)
	{
		LookRight(t, true);
	}
}
#pragma endregion

