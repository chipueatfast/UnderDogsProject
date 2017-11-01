#include "GameObject.h"
#include "dxgraphics.h"


GameObject::GameObject()
{
	width = 0;
	height = 0;
	_scale = D3DXVECTOR2(1, 1);
	_translation = D3DXVECTOR2(0, 0);
	_angel = 0;
}


GameObject::~GameObject()
{
}

int GameObject::getWidth()
{
	return width;
}

int GameObject::getHeight()
{
	return height;
}

void GameObject::setWidth(int value)
{
	width = value;
}

void GameObject::setHeight(int value)
{
	height = value;
}

float GameObject::getX()
{
	return _position.x;
}

float GameObject::getY()
{
	return _position.y;
}

D3DXVECTOR3 GameObject::getPosition()
{
	return _position;
}

void GameObject::setPosition(D3DXVECTOR3 vec3)
{
	_position = vec3;
}

void GameObject::setPosition(float x, float y)
{
	_position = D3DXVECTOR3(x, y, 0);
}

void GameObject::setScale(D3DXVECTOR2 scale)
{
	_scale = scale;
}

void GameObject::setTranslation(D3DXVECTOR2 trans)
{
	_translation = trans;
}

void GameObject::setAngel(float angel)
{
	_angel = angel;
}

void GameObject::Transform(D3DXVECTOR2 Translation, float Rotation, D3DXVECTOR2 Scale, D3DXVECTOR2 center)
{
	D3DXMATRIX  mMatrix;
	float mRotation = 0;
	D3DXVECTOR2 mTranslation = Translation;
	D3DXVECTOR2 mScale = Scale;
	D3DXVECTOR2 mRotationCenter;
	if (center == D3DXVECTOR2(0, 0))
		mRotationCenter = D3DXVECTOR2(this->getX() + this->width / 2, this->getY() + this->height / 2);
	else
		mRotationCenter = center;

	D3DXMatrixTransformation2D(&mMatrix, &mRotationCenter, 0, &mScale, &mRotationCenter,
		mRotation, &mTranslation);
	D3DXMATRIX oldMatrix;
	sprite_handler->GetTransform(&oldMatrix);
	sprite_handler->SetTransform(&mMatrix);
	Render();
	sprite_handler->SetTransform(&oldMatrix);
}

void GameObject::Render()
{
	 _sprite->Render(getX(),getY());
}
