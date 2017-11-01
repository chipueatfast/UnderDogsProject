#include "GameObject.h"
#include "dxgraphics.h"


GameObject::GameObject()
{
	width = 0;
	height = 0;
	setScale(D3DXVECTOR2(1, 1));
	D3DXMatrixTranslation(&_translation,_position.x,_position.y,0);
	setAngel(0);
	_sprite = new Sprite();
}


GameObject::~GameObject()
{
}

void GameObject::setSprite(Sprite * t)
{
	_sprite = t;
	width = _sprite->width();
	height = _sprite->height();
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
	D3DXMatrixTranslation(&_translation, _position.x, _position.y, 0);
}

void GameObject::setPosition(float x, float y)
{
	_position = D3DXVECTOR3(x, y, 0);
	D3DXMatrixTranslation(&_translation, x, y, 0);
}

void GameObject::setScale(D3DXVECTOR2 scale)
{
	D3DXMatrixScaling(&_scale, scale.x, scale.y, .0f);
}

void GameObject::setAngel(float angel)
{
	D3DXMatrixRotationZ(&_rotation, D3DXToRadian(angel));
}

void GameObject::Rotation(float angel)
{
	setAngel(angel);
	D3DXMATRIX oldMatrix;
	sprite_handler->GetTransform(&oldMatrix);
	sprite_handler->SetTransform(&(_rotation*_translation));
	Render();
	sprite_handler->SetTransform(&oldMatrix);
}

void GameObject::Scale(D3DXVECTOR2 scale)
{
	setScale(scale);
	D3DXMATRIX oldMatrix;
	sprite_handler->GetTransform(&oldMatrix);
	sprite_handler->SetTransform(&(_scale*_translation));
	Render();
	sprite_handler->SetTransform(&oldMatrix);
}



void GameObject::Flip()
{

	Scale(D3DXVECTOR2(-1, 1));
}

void GameObject::Transform( float Rotation, D3DXVECTOR2 Scale, D3DXVECTOR2 Translation)
{
	D3DXMATRIX  mMatrix;
	float mRotation = Rotation;
	D3DXVECTOR2 mTranslation = Translation;
	D3DXVECTOR2 mScale = Scale;
	D3DXVECTOR2 mRotationCenter;
	mRotationCenter = D3DXVECTOR2(this->getX(), this->getY());

	D3DXMatrixTransformation2D(&mMatrix, &mRotationCenter, 0, &mScale, &mRotationCenter,
		mRotation, &mTranslation);
	D3DXMATRIX oldMatrix;
	sprite_handler->GetTransform(&oldMatrix);
	sprite_handler->SetTransform(&mMatrix);
	Render();
	sprite_handler->SetTransform(&oldMatrix);
}

void GameObject::Render(D3DXVECTOR3* AnchorPoint)
{
	RECT cameraSheet;
	cameraSheet.top = (_sprite->index() / _sprite->sprites_per_row())*_sprite->height() + 1;
	cameraSheet.bottom = cameraSheet.top + _sprite->height() + 1;
	cameraSheet.left = 2 + (_sprite->index()%_sprite->sprites_per_row())* _sprite->width();
	cameraSheet.right = cameraSheet.left + _sprite->width() - 2;

	if (AnchorPoint == NULL)
	{
		AnchorPoint = new D3DXVECTOR3(width / 2,height / 2, 0);
	}
	D3DXVECTOR3 position;

	sprite_handler->Draw(
		_sprite->image(),
		&cameraSheet,
		AnchorPoint,
		NULL,
		D3DCOLOR_XRGB(255, 255, 255)
	);

}

void GameObject::Update()
{
}
