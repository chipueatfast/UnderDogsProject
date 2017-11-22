#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
//06-11 zPhong

#define FRICTION 0.1f
#define BODER_SIZE 50*SCALE_RATE

#include "d3d9.h"
#include "d3dx9.h"

class MyCamera : public GameObject
{
private:
	static MyCamera* _instance;
	RECT _viewRect;
	bool _isStopX = true;
	bool _isStopY = true;

	float _distanceUpDown;
	
	long _curMapWidth, _curMapHeight;
	int _vxTranslate;
public:
	int vxTranslate() const
	{
		return _vxTranslate;
	}

private:
	int _vyTranslate;
	float _distanceLeftRight;
public:
	float distanceLeftRight() const
	{
		return _distanceLeftRight;
	}

	long curMapWidth() const
	{
		return _curMapWidth;
	}

	long curMapHeight() const
	{
		return _curMapHeight;
	}
	 
	void setCurMapWidth(long curMapWidth)
	{
		_curMapWidth = curMapWidth;
	}

	void setCurMapHeight(long curMapHeight)
	{
		_curMapHeight = curMapHeight;
	}

	MyCamera();
	void Update(float t);
	~MyCamera();
	static MyCamera* GetInstance();

	RECT View();
	RECT ExtraView();
	void StopX()
	{
		_vx = 0;
		_isStopX = true;
	}
	void StopY()
	{
		_vy = 0;
		_isStopY = true;
	}
	void MoveX() { _isStopX = false; }
	void MoveY() { _isStopY = false; }

	void LookUp(float t,bool toNormal);
	void LookDown(float t, bool toNormal);
	void set_curFace(GameObject::Face face, int mainCharacter_x, int mainCharacter_y);
	void LookLeft(float t, bool toNormal);
	void LookRight(float t, bool toNormal);
	void LeftRightToNormal(float t);
public:
	float vx() const
	{
		return _vx;//*(1 + FRICTION);
	}

	void setVx(float vx)
	{
		_vx = vx;// *(1 + FRICTION);
	}

	float vy() const
	{
		return _vy; 
	}

	void setVy(float vy)
	{
		_vy = vy;
	}

	float getDistanceUpDown()
	{
		return _distanceUpDown;
	}

};
#endif