#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
//06-11 zPhong

#define FRICTION 0.1f

#include "d3d9.h"
#include "d3dx9.h"

class MyCamera : public GameObject
{
private:
	static MyCamera* _instance;
	RECT _viewRect;
	bool _isStop = true;
	float _distanceUpDown;
	
	long _curMapWidth, _curMapHeight;
 	 
public:


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
	void Stop() { _vx = 0; }
	void Move() { _isStop = false; }
	void LookUp(float t,bool toNormal);
	void LookDown(float t, bool toNormal);
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