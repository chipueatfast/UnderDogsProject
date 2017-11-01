
#ifndef  _GAME_OBJECT_H_
#define  _GAME_OBJECT_H_

#include "sprite.h"


class GameObject
{
private:
	Sprite* _sprite;
	int width, height;
	D3DXVECTOR3 _position;
	D3DXMATRIX _scale;
	D3DXMATRIX _translation;
	D3DXMATRIX _rotation;

public:
	GameObject();
	~GameObject();
	void setSprite(Sprite* t);
	int getWidth();
	int getHeight();
	void setWidth(int value);
	void setHeight(int value);
	float getX();
	float getY();
	D3DXVECTOR3 getPosition();
	void setPosition(D3DXVECTOR3 vec3);
	void setPosition(float x, float y);
	void setScale(D3DXVECTOR2 scale);
	void setAngel(float angel);

	void Rotation(float angel);
	void Scale(D3DXVECTOR2 scale);

	void Flip();
	void Transform(float Rotation = 0, D3DXVECTOR2 Scale = D3DXVECTOR2(1, 1),D3DXVECTOR2 Translation = D3DXVECTOR2(0,0));
	void Render(D3DXVECTOR3* AnchorPoint = NULL);
	void Update();
};

#endif // ! _GAME_OBJECT_H_