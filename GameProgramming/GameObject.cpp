#include "GameObject.h"
#include "dxgraphics.h"
//new on 02-11, zPhong
GameObject::GameObject()
{
	_width = 0;
	_height = 0;
	setScale(D3DXVECTOR2(1, 1));
	D3DXMatrixTranslation(&_translation, _position.x, _position.y, 0);
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
	D3DXMatrixTranslation(&_translation, _position.x, _position.y, 0);
	if (_sprite!= NULL)
	{
		RECT temp_rect;
		temp_rect.top = y();
		temp_rect.bottom = y() + height();
		temp_rect.left = x();
		temp_rect.right = x() + width();
		_boundingBox = temp_rect;	
	}
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

void GameObject::setAngle(float angle)
{
	D3DXMatrixRotationZ(&_rotation, D3DXToRadian(angle));
}

void GameObject::setTranslation(D3DXVECTOR2 vec)
{
	D3DXMatrixTranslation(&_translation, vec.x, vec.y, 0);
}

void GameObject::Rotation(float angle)
{
	setAngle(angle);
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

void GameObject::Transform(float Rotation, D3DXVECTOR2 Scale, D3DXVECTOR2 Translation)
{
	D3DXMATRIX  mMatrix;
	float mRotation = Rotation;
	D3DXVECTOR2 mTranslation = Translation;
	D3DXVECTOR2 mScale = Scale;
	D3DXVECTOR2 mRotationCenter;
	mRotationCenter = D3DXVECTOR2(this->x(), this->y());

	D3DXMatrixTransformation2D(&mMatrix, &mRotationCenter, 0, &mScale, &mRotationCenter,
		mRotation, &mTranslation);
	D3DXMATRIX oldMatrix;
	sprite_handler->GetTransform(&oldMatrix);
	sprite_handler->SetTransform(&mMatrix);
	Render(&_anchorPoint);
	sprite_handler->SetTransform(&oldMatrix);
}

void GameObject::Render(D3DXVECTOR3* AnchorPoint)
{
	sprite_handler->Draw(
		_sprite->image(),
		NULL,
		&_anchorPoint,
		&_position,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}


void GameObject::Translation(D3DXVECTOR2 vec)
{
	setTranslation(vec);
	D3DXMATRIX oldMatrix;
	sprite_handler->GetTransform(&oldMatrix);
	sprite_handler->SetTransform(&_translation);
	Render(&_anchorPoint);
	sprite_handler->SetTransform(&oldMatrix);
}

void GameObject::Update(float t)
{
}












