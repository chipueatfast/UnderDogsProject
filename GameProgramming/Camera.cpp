#include "dxgraphics.h"
#include "game.h"
#include <map>
#include "Camera.h"
#include "trace.h"
#include "Scene1.h"
#define MAX_LOOKUP -_height/6
#define MAX_LOOKDOWN _height/6
#define BORDER_SIZE 75*SCALE_RATE;
MyCamera* MyCamera::_instance = NULL;



MyCamera::MyCamera()
{
	_distanceUpDown = 0;
	_distanceLeftRight = 0;
	_distanceJumpFall = 0;
	_width = SCREEN_WIDTH / SCALE_RATE;		//width cua viewRect
	_height = SCREEN_HEIGHT / SCALE_RATE;	//height cua viewRect
	_viewRect = RECT();
	_position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	_anchor = MIDDLE;
	CalAnchorPoint();
	_vx = 0;
	_vy = 0;
	_curFace = Face::RIGHT;
	_vxTranslate = 0;
	_vyTranslate = 0;

	while (_maxLookRight <= float(_width) / 6)
	{
		_maxLookRight += CHARACTER_VX * FIXED_TIME;
	}
	_maxLookLeft = -_maxLookRight;

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

	extraView.left = _viewRect.left - BORDER_SIZE;
	extraView.top = _viewRect.top  - BORDER_SIZE;
	extraView.bottom = _viewRect.bottom + BORDER_SIZE;
	extraView.right = _viewRect.right + BORDER_SIZE;
	return extraView;
}

void MyCamera::RenderBounding(D3DCOLOR color, bool isRotation, bool isScale, bool isTranslation)
{
	setTranslation(D3DXVECTOR2(ExtraView().left - _viewRect.left, ExtraView().bottom - _viewRect.bottom));
	Transform(isRotation, isScale, isTranslation);

	RECT srect;
	srect.top = 0;
	srect.left = 0;
	srect.bottom = _height / 2;
	srect.right = _width / 2;

	sprite_handler->Draw(
		_boundingRect->image(),
		&srect,
		&CalAnchorPoint(TOP_LEFT),
		NULL,
		color
	);
	sprite_handler->SetTransform(&old_matrix);
}

#pragma region UPDOWN
void MyCamera::LookUp(float t, bool toNormal)
{

	_vyTranslate = -15;

	if (((_distanceUpDown + _vyTranslate*t <= MAX_LOOKUP || _distanceUpDown + _vyTranslate*t >= MAX_LOOKDOWN) && toNormal == false) // dat toi bien tren hoac bien duoi cua tam nhin
		|| _distanceUpDown + _vyTranslate*t <= (_height / 2 - _position.y) //dat toi cot moc bien tren cua map buffer
		|| (toNormal == true && int(_distanceUpDown) == 0)) // da dat toi tam nhin man hinh binh thuong mong muon
	{
		_vyTranslate = 0;
	}

	_distanceUpDown += _vyTranslate*t;
}

//Update(0);


void MyCamera::LookDown(float t, bool toNormal)
{

	_vyTranslate = 15;
	//trace(L"_distanceUpDown=%f cuMapHeight/2= %f  - _positionY = %f", _distanceUpDown, _curMapHeight / 2, _position.y);

	if (((_distanceUpDown + _vyTranslate*t <= MAX_LOOKUP || _distanceUpDown + _vyTranslate*t >= MAX_LOOKDOWN) && toNormal == false) //dat toi bien bien tren hoac bien duoi cua tam nhin
		|| _distanceUpDown + _vyTranslate*t >= _curMapHeight / 2 - _height / 2 - _position.y //dat toi bien duoi cua mapbuffer
		|| (toNormal == true && int(_distanceUpDown) == 0)) //da dat toi tam nhin binh thuong mong muon
	{
		_vyTranslate = 0;
	}

	_distanceUpDown += _vyTranslate*t;
	//trace(L"%f", _distanceUpDown);

}


void MyCamera::UpDownToNormal(float t)
{
	_vyTranslate = 0;
	if (_distanceUpDown > 0)
	{
		LookUp(t, true);
	}
	if (_distanceUpDown < 0)
	{
		LookDown(t, true);
	}
}

#pragma endregion 


void MyCamera::Update(float t)
{
	_distanceLeftRight += _vxTranslate*t;
	_position.x += (_vxTranslate)*t + (_vx)*t;;

	_position.y += _vy*t + _vyTranslate*t;


	//Lock camera Y


	//Raw fix camera left right bounding
	if (_position.x < _width / 2)
		_position.x = _width / 2;
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

	_viewRect.left = _position.x - _width / 2;
	_viewRect.right = _position.x + _width / 2;
	_viewRect.top = -_height / 2 + _position.y;
	_viewRect.bottom = _viewRect.top + _height;
	_boundingBox = ExtraView();
}

#pragma region LEFTRIGHT 

void MyCamera::LookLeft(float t, bool toNormal)
{
	_vxTranslate = -CHARACTER_VX;
	if (((_distanceLeftRight + int(_vxTranslate*t) < _maxLookLeft) && _curFace == Face::RIGHT)
		//	|| _distanceLeftRight + _vxTranslate*t <= (_width/2 - _position.x) 
		|| (toNormal == true && int(_distanceLeftRight) == 0))
	{
		_vxTranslate = 0;
	}
}

void MyCamera::LookRight(float t, bool toNormal)
{
	_vxTranslate = CHARACTER_VX;

	if (((_distanceLeftRight + int(_vxTranslate*t) > _maxLookRight) && _curFace == Face::LEFT) //khi vuot qua vi tri toi da
																							   //	 || _distanceLeftRight + _vxTranslate*t >= (_curMapWidth + _width / 2 - _position.x )
		|| (toNormal == true && int(_distanceLeftRight) == 0)) // khi dang muon tro ve vi tri can bang va da dat duoc vi tri can bang
	{
		_vxTranslate = 0;
	}
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

int MyCamera::getUpperHeight()
{
	return this->y() - _height / 4;
}

int MyCamera::getLowerHeight()
{
	return this->y() + _height / 6;
}

void MyCamera::set_curFace(Face face)
{
	if (face != _curFace)
	{
		_curFace = face;
		switch (face)
		{
		case Face::LEFT:
			_distanceLeftRight = _distanceLeftRight + (_maxLookRight) * 2;
			break;
		case Face::RIGHT:
			_distanceLeftRight = _distanceLeftRight + (_maxLookLeft) * 2;
			break;
		}
	}
}
#pragma endregion
