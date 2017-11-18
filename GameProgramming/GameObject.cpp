#include "GameObject.h"
#include "dxgraphics.h"
#include "game.h"
#include "trace.h"
//new on 02-11, zPhong
GameObject::GameObject()
{
	_stateManager = new StateManager();
	_position.x = 0;
	_position.y = 0;
	_width = 0;
	_height = 0;
	setScale(D3DXVECTOR2(SCALE_RATE, SCALE_RATE));
	_translation = D3DXVECTOR2(_position.x, _position.y);
	setAngle(0);
	_sprite = new Sprite();
	_anchor = AnchorPoint::TOP_LEFT;
	_index = 0;
	_animaDelay = 1.0f;
	_animaCount = 0;

	_boundingRect = new Sprite("Res/blank.png", 50, 50);
}
GameObject::~GameObject()
{
}

void GameObject::setSprite(Sprite * t)
{
	_sprite = t;
	_width = t->width();
	_height = t->height();
	_boundingBox = CalculateBoundingBox(x(), y(), _width, _height, _anchor);
}

bool GameObject::CheckFlip()
{
	//neu face frame nay bang face frame truoc thi khoi flip
	if (_curFace != _lastFace)
	{
		_lastFace = _curFace;
		return true;
	}
	else return false;
}
D3DXVECTOR3 GameObject::CalPositon(AnchorPoint anchor)
{
	return _position - CalAnchorPoint(_anchor) + CalAnchorPoint(anchor);
}

D3DXVECTOR3 GameObject::Position()
{
	return _position;
}
void GameObject::setPosition(D3DXVECTOR3 vec3)
{
	_position = vec3;
	_translation = D3DXVECTOR2(_position.x, _position.y);// test
}
void GameObject::setPosition(float x, float y)
{
	_position = D3DXVECTOR3(x, y, 0);
		_translation = D3DXVECTOR2(_position.x, _position.y); // test
	_boundingBox = CalculateBoundingBox(x, y, _width, _height, _anchor);
}

void GameObject::setScale(D3DXVECTOR2 scale)
{
	_scale = scale;
}

void GameObject::setAngle(float angle)
{
	_angle = angle;
}

void GameObject::setTranslation(D3DXVECTOR2 vec)
{
	_translation = vec;
}


void GameObject::Flip()
{
	_scale.x = _scale.x*(-1);
}

void GameObject::Transform(bool isRotation, bool isScale, bool isTranslation)
{
	float mRotation;

	D3DXMATRIX  mMatrix;
	D3DXVECTOR2 mTranslation;
	D3DXVECTOR2 mScale;
	if (isRotation == true)
		mRotation = _angle;
	else
		mRotation = 0;
	if (isTranslation == true)
		mTranslation = _translation*SCALE_RATE;
	else
		mTranslation = D3DXVECTOR2(0, 0);
	if (isScale == true)
		mScale = _scale;
	else
		mScale = D3DXVECTOR2(SCALE_RATE, SCALE_RATE);

	D3DXMATRIX rota, trans, scale;

	D3DXMatrixScaling(&scale, mScale.x, mScale.y, 1);
	D3DXMatrixTranslation(&trans, mTranslation.x, mTranslation.y, 0);
	D3DXMatrixRotationX(&rota, mRotation);

	mMatrix = scale*trans*rota;

	sprite_handler->SetTransform(&mMatrix);
}
void GameObject::UpdateAnimate(bool isRepeating)
{
	_animaCount ++;
	if (_animaCount >= _animaDelay)
	{
		if (isRepeating == false)
			Next2();
		else
			Next();
		_animaCount = 0;
		// update lai anchorpoint do frame co bounding khac nhau
		CalAnchorPoint();
	}
}

void GameObject::RenderBounding(D3DCOLOR color, bool isRotation, bool isScale, bool isTranslation)
{
	Transform(isRotation, isScale, isTranslation);

	RECT srect;
	srect.top = 0;
	srect.left = 0;
	srect.bottom = _height;
	srect.right = _width;

	sprite_handler->Draw(
		_boundingRect->image(),
		&srect,
		&_anchorPoint,
		NULL,
		color
	);
	sprite_handler->SetTransform(&old_matrix);
}

void GameObject::Render(bool isRotation, bool isScale, bool isTranslation)
{
	//D3DXMATRIX oldmatrix;
	//sprite_handler->GetTransform(&oldmatrix);
	//

	Transform(isRotation, isScale, isTranslation);

	if (_stateManager->curState().getName() == "") {
		sprite_handler->Draw(_sprite->image(), NULL, &_anchorPoint, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}
	else
	{
		_width = _stateManager->curState().getListRect().at(_index).right - _stateManager->curState().getListRect().at(_index).left;
		_height = _stateManager->curState().getListRect().at(_index).bottom - _stateManager->curState().getListRect().at(_index).top;
		_boundingBox = CalculateBoundingBox(x(), y(), _width, _height, _anchor);
		CalAnchorPoint();


		sprite_handler->Draw(
			_sprite->image(),
			//_stateManager == NULL ? NULL : &_stateManager->curState().getListRect().at(_index),
			_stateManager->curState().getName() == "" ? NULL : &_stateManager->curState().getListRect().at(_index),
			//NULL,
			&_anchorPoint,
			NULL,
			D3DCOLOR_XRGB(255, 255, 255)
		);

		sprite_handler->SetTransform(&old_matrix);
	}

}


void GameObject::Update(float t)
{
}

void GameObject::GraphicUpdate(float t)
{
	if (_stateManager != NULL)
	{
		_animaCount += t;
		if (_animaCount >= _animaDelay)
		{

			Next();
			_animaCount = 0;
			// update lai anchorpoint do frame co bounding khac nhau
			//CalAnchorPoint();
		}

		
	}
}

void GameObject::Next()
{
	int size = _stateManager->curState().getListRect().size() - 1;
	if (size > 0)
		_index = (_index + 1) % size;
	else
		_index = 0;
}

void GameObject::Next2()
{
	int size = _stateManager->curState().getListRect().size() - 1;
	if (_index < size)
		_index++;
}

void GameObject::set_state(string newState)
{
	if (_stateManager->curState().getName() != _stateManager->dict_state()[newState])
	{
		_stateManager->setState(newState);
		Reset();

	}

	

}

void GameObject::Reset()
{
	_index = 0;
}

//
void GameObject::CalAnchorPoint()
{
	switch (_anchor)
	{
	case TOP_LEFT:
	{
		_anchorPoint = D3DXVECTOR3(0, 0, 0);

	}; break;
	case TOP_MID:
	{
		_anchorPoint = D3DXVECTOR3(_width / 2, 0, 0);
	}; break;
	case TOP_RIGHT:
	{
		_anchorPoint = D3DXVECTOR3(_width, 0, 0);
	}; break;
	case MID_LEFT:
	{
		_anchorPoint = D3DXVECTOR3(0, _height / 2, 0);
	}; break;
	case MIDDLE:
	{
		_anchorPoint = D3DXVECTOR3(_width / 2, _height / 2, 0);
	}; break;
	case MID_RIGHT:
	{
		_anchorPoint = D3DXVECTOR3(_width, _height / 2, 0);
	}; break;
	case BOTTOM_LEFT:
	{
		_anchorPoint = D3DXVECTOR3(0, _height, 0);
	}; break;

	case BOTTOM_MID:
	{
		_anchorPoint = D3DXVECTOR3(_width / 2, _height, 0);
	}; break;
	case BOTTOM_RIGHT:
	{
		_anchorPoint = D3DXVECTOR3(_width, _height, 0);
	}; break;
	}
}
D3DXVECTOR3 GameObject::CalAnchorPoint(AnchorPoint type)
{
	D3DXVECTOR3 anchorPoint;
	switch (type)
	{
	case TOP_LEFT:
	{
		anchorPoint = D3DXVECTOR3(0, 0, 0);
	}; break;
	case TOP_MID:
	{
		anchorPoint = D3DXVECTOR3(_width / 2, 0, 0);
	}; break;
	case TOP_RIGHT:
	{
		anchorPoint = D3DXVECTOR3(_width, 0, 0);
	}; break;
	case MID_LEFT:
	{
		anchorPoint = D3DXVECTOR3(0, _height / 2, 0);
	}; break;
	case MIDDLE:
	{
		anchorPoint = D3DXVECTOR3(_width / 2, _height / 2, 0);
	}; break;
	case MID_RIGHT:
	{
		anchorPoint = D3DXVECTOR3(_width, _height / 2, 0);
	}; break;
	case BOTTOM_LEFT:
	{
		anchorPoint = D3DXVECTOR3(0, _height, 0);
	}; break;

	case BOTTOM_MID:
	{
		anchorPoint = D3DXVECTOR3(_width / 2, _height, 0);
	}; break;
	case BOTTOM_RIGHT:
	{
		_anchorPoint = D3DXVECTOR3(_width, _height, 0);
	}; break;
	}
	return anchorPoint;
}
RECT GameObject::getBoundingBox(string stateCode)
{
	State t;
	t = _stateManager->getStateByCode(stateCode);
	long width = t.getListRect().at(0).right - t.getListRect().at(0).left;
	long height = t.getListRect().at(0).bottom - t.getListRect().at(0).top;
	return CalculateBoundingBox(x(), y(), width, height,_anchor);
}

