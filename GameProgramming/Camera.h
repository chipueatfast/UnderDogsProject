#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
//06-11 zPhong

#define CHARACTER_VX 20

#include "d3d9.h"
#include "d3dx9.h"
#include <list>

class MyCamera : public GameObject
{


private:
	static MyCamera* _instance;
	RECT _viewRect;
	bool _isStopY = true;
	long _curMapWidth, _curMapHeight;
	int _distanceUpDown;
	int _distanceLeftRight;
	int _distanceJumpFall;

	std::list <int> * _mainCharacterVy = new list<int>;

	int _vxTranslate;
	int _vyTranslate;
	int _vyJumpFall;
	int _maxLookLeft;
	int _maxLookRight;
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
	RECT ExtraView();
	void RenderBounding(D3DCOLOR color = D3DCOLOR_ARGB(0, 255, 255, 255), bool isRotation = false, bool isScale = false, bool isTranslation = true);

	void StopY()
	{
		_vy = 0;
		_isStopY = true;
	}

	void MoveY() { _isStopY = false; }
	void LookUp(float t, bool toNormal);
	void LookDown(float t, bool toNormal);
	void LookLeft(float t, bool toNormal);
	void LookRight(float t, bool toNormal);
	void UpDownToNormal(float t);
	void LeftRightToNormal(float t);
public:
	int vx() const
	{
		return _vx;
	}

	void setVx(float vx)
	{
		_vx = vx;

	}

	int vy() const
	{
		return _vy;
	}

	void setVy(float vy)
	{
		_vy = vy;
	}

	int getUpperHeight();

	int getLowerHeight();


	int getDistanceUpDown()
	{
		return _distanceUpDown;
	}
	int getDistanceLeftRight()
	{
		return _distanceLeftRight;
	}

	int getMaxLookRight()
	{
		return _maxLookRight;
	}

	long getCurMapWidth()
	{
		return _curMapWidth;
	}

	void setVxTranslate(int vxTranslate)
	{
		_vxTranslate = vxTranslate;
	}
	void setDistanceLeftRight(int distanceLeftRight)
	{
		_distanceLeftRight = distanceLeftRight;
	}

	void set_curFace(Face face);

};
#endif