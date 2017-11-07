#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
//06-11 zPhong

#include "d3d9.h"
#include "d3dx9.h"

class MyCamera
{
private:
	static MyCamera* _instance;
	int _width, _height;
	RECT _viewRect;
	D3DXVECTOR3 _position;
	bool _isStop = true;
	float _vx, _vy;
	long _curMapWidth, _curMapHeight;
public:
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
	D3DXVECTOR3 Position();
	RECT View();
	void Stop() { _isStop = true; }
	void Move() { _isStop = false; }
	void LookUp();
public:
	float vx() const
	{
		return _vx;
	}

	void setVx(float vx)
	{
		_vx = vx;
	}

	float vy() const
	{
		return _vy;
	}

	void setVy(float vy)
	{
		_vy = vy;
	}
};
#endif