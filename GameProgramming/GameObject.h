#ifndef  _GAME_OBJECT_H_
#define  _GAME_OBJECT_H_
//update 02-11 chipu
#include "sprite.h"


class GameObject
{
private:
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

private:
	RECT _boundingBox;
	D3DXVECTOR3 _position;
	D3DXMATRIX _scale;
	D3DXMATRIX _translation;
	D3DXMATRIX _rotation;

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
	int x() const 
	{
		return _position.x;
	};
	int y() const 
	{
		return _position.y;
	}
	D3DXVECTOR3 getPosition();
	void setPosition(D3DXVECTOR3 vec3);
	void setPosition(float x, float y);
	void setScale(D3DXVECTOR2 scale);
	void setAngle(float angle);

	void Rotation(float angel);
	void Scale(D3DXVECTOR2 scale);

	void Flip();
	void Transform(float Rotation = 0, D3DXVECTOR2 Scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 Translation = D3DXVECTOR2(0, 0));
	void Render(D3DXVECTOR3* AnchorPoint = NULL);
	void Update();
};

#endif // ! _GAME_OBJECT_H_