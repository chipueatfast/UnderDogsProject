#include "GameObject.h"
#include "dxgraphics.h"
#include "game.h"

RECT GameObject::GetBoundingBox(string stateCode)
{
	State t;
	t = _stateManager->GetStateByCode(stateCode);
	long width = t.getListRect().at(0).right - t.getListRect().at(0).left;
	long height = t.getListRect().at(0).bottom - t.getListRect().at(0).top;
	return CalculateBoundingBox(x(), y(), width, height);
}

void GameObject::UpdateAnimate(bool isRepeating, float deltaTime)
{
	_animaCount += deltaTime;
	if (_animaCount >= _animadelay)
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

//new on 02-11, zPhong
GameObject::GameObject()
{
	_stateManager = NULL;
	_width = 0;
	_height = 0;
	setScale(D3DXVECTOR2(1, 1));
	_translation = D3DXVECTOR2(_position.x, _position.y);
	setAngle(0);
	_sprite = new Sprite();
}
GameObject::~GameObject()
{
}

void GameObject::setSprite(Sprite * t)
{
	if (t!=nullptr)
	{
		_sprite = t;
		_width = t->width();
		_height = t->height();
		_boundingBox = CalculateBoundingBox(x(), y(), _width, _height);
	}

}

bool GameObject::CheckFlip()
{

	if (_curface != _lastface)
	{
		_lastface = _curface;
		return true;
	}
	else return false;
}

D3DXVECTOR3 GameObject::getPosition()
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
	_boundingBox = CalculateBoundingBox(x, y, _width, _height);
}
D3DXVECTOR3 GameObject::CalPositon(AnchorPoint anchor)
{
	return _position - CalAnchorPoint(_anchor) + CalAnchorPoint(anchor);
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
	D3DXMATRIX  mMatrix;
	float mRotation;
	D3DXVECTOR2 mTranslation;
	D3DXVECTOR2 mScale;
	if (isRotation == true)
		mRotation = _angle;
	else
		mRotation = 0;
	if (isTranslation == true)
		mTranslation = _translation;
	else
		mTranslation = D3DXVECTOR2(0, 0);
	if (isScale == true)
		mScale = _scale;
	else
		mScale = D3DXVECTOR2(1, 1);

	D3DXMATRIX rota, trans, scale;
	D3DXMatrixScaling(&scale, mScale.x, mScale.y, 1);
	D3DXMatrixTranslation(&trans, mTranslation.x, mTranslation.y, 0);
	D3DXMatrixRotationX(&rota, mRotation);

	mMatrix = scale*trans*rota;

	sprite_handler->SetTransform(&mMatrix);
}

void GameObject::Render(bool isRotation, bool isScale, bool isTranslation)
{
	//D3DXMATRIX oldmatrix;
	//sprite_handler->GetTransform(&oldmatrix);
	Transform(isRotation, isScale, isTranslation);

	sprite_handler->Draw(
		_sprite->image(),
		_stateManager == NULL ? NULL : &_stateManager->curState().getListRect().at(_index),
		&_anchorPoint,
		NULL,
		D3DCOLOR_XRGB(255, 255, 255)
	);

	sprite_handler->SetTransform(&old_matrix);

}


void GameObject::Update(float t)
{
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
