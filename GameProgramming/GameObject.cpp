#include "GameObject.h"
#include "dxgraphics.h"
//new on 02-11, zPhong
GameObject::GameObject()
{
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
	_sprite = t;
	_width = t->width();
	_height = t->height();
	RECT temp_rect;
	temp_rect.top = y();
	temp_rect.bottom = y() + height();
	temp_rect.left = x();
	temp_rect.right = x() + width();
	_boundingBox = temp_rect;
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

void GameObject::Render(AnchorPoint type, bool isRotation, bool isScale, bool isTranslation)
{

}


void GameObject::Update(float t)
{
}

void GameObject::calAnchorPoint()
{
	switch (_anchor)
	{
	case MIDDLE:
	{
		_anchorPoint = D3DXVECTOR3(_width / 2, _height / 2, 0);
	}; break;
	case BOTTOM_MID:
	{
		_anchorPoint = D3DXVECTOR3(_width / 2, _height, 0);
	}; break;
	}
}
D3DXVECTOR3 GameObject::calAnchorPoint(AnchorPoint type)
{
	D3DXVECTOR3 anchorPoint;
	switch (type)
	{
	case MIDDLE:
	{
		anchorPoint = D3DXVECTOR3(_width / 2, _height / 2, 0);
	}; break;
	case BOTTOM_MID:
	{
		anchorPoint = D3DXVECTOR3(_width / 2, _height, 0);
	}; break;
	}
	return anchorPoint;
}













