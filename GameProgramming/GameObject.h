#ifndef  _GAME_OBJECT_H_
#define  _GAME_OBJECT_H_
//update 02-11 chipu
#include "sprite.h"

enum AnchorPoint
{
	TOP_LEFT,
	TOP_MID,
	TOP_RIGHT,
	MID_LEFT,
	MIDDLE,
	MID_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_MID,
	BOTTOM_RIGHT
};

class GameObject
{
protected:
	Sprite* _sprite;
	int _width, _height;
	float _vx, _vy;
public:
	float vx() const
	{
		return _vx;
	}

	void set_vx(float vx)
	{
		_vx = vx;
	}

	float vy() const
	{
		return _vy;
	}

	void set_vy(float vy)
	{
		_vy = vy;
	}

	RECT bounding_box() const
	{
		return _boundingBox;
	}

	void set_bounding_box(const RECT& tag_rect)
	{
		_boundingBox = tag_rect;
	}

protected:
	RECT _boundingBox;
	D3DXVECTOR3 _position;
	D3DXVECTOR2 _scale;
	D3DXVECTOR2 _translation;
	float _angle;
	AnchorPoint _anchor;
public:
	AnchorPoint anchor() const
	{
		return _anchor;
	}

	void setAnchor(AnchorPoint anchor)
	{
		_anchor = anchor;
	}

protected:
	D3DXVECTOR3 _anchorPoint;

public:

	int width() const
	{
		return _width;
	}

	void set_width(int width)
	{
		_width = width;
	}

	int height() const
	{
		return _height;
	}

	void set_height(int height)
	{
		_height = height;
	}
	GameObject();
	~GameObject();
	void setSprite(Sprite* t);
	float x() const
	{
		return _position.x;
	};
	float y() const
	{
		return _position.y;
	}
	D3DXVECTOR3 getPosition();
	void setPosition(D3DXVECTOR3 vec3);
	void setPosition(float x, float y);
	void setScale(D3DXVECTOR2 scale);
	void setAngle(float angle);
	void setTranslation(D3DXVECTOR2 vec);
	void Flip();
	virtual void Render(AnchorPoint type = AnchorPoint::MIDDLE, bool isRotation = false, bool isScale = false, bool isTranslation = true) = 0;
	void Update(float t);
protected:
	void calAnchorPoint(); // tinh lai gia tri anchor cua class
	D3DXVECTOR3 calAnchorPoint(AnchorPoint type); // tra ve anchorpoint theo type truyen vao
	void Transform(bool isRotation, bool isScale, bool isTranslation); // apply matrix transform vao spriteHandler
};

#endif // ! _GAME_OBJECT_H_