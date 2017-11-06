#pragma once
#ifndef _SCENE1_H
#define _SCENE1_H
#include "game.h"
#include "Aladdin.h"
#include "MyCamera.h"
class Scene1: public Game
{
private:
	virtual void Key_Pressed(int KeyCode) override;
	virtual void InputUpdate() override;
	virtual void PhysicsUpdate() override;
	virtual void GraphicUpdate(float t) override;
	Aladdin* character;
	LPDIRECT3DSURFACE9 background;
	LPDIRECT3DTEXTURE9 mapETC[2];
	D3DXIMAGE_INFO* mapinfo;
	RECT viewRect;
public:
	int Game_Init(HWND) override;
	void Game_Run(HWND) override;
	void Game_End(HWND) override;
	Scene1();
	~Scene1();
};
#endif

