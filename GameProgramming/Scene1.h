#pragma once
#ifndef _SCENE1_H
#define _SCENE1_H
#include"Aladdin.h"
#include "game.h"
#include <list>
#include <d3dx9.h>

class Scene1: public Game
{
private:
	Aladdin* mainCharacter;
	CSound* _soundJump;
	LPDIRECT3DSURFACE9 background;
	LPDIRECT3DTEXTURE9 mapETC[2];
	D3DXIMAGE_INFO* mapinfo;
	RECT viewRect;
	list<GameObject*>* object_list;
	virtual void CollisionDetect() override;
	virtual void Key_Pressed(int KeyCode) override;
	virtual void InputUpdate() override;
	virtual void PhysicsUpdate(float) override;
	virtual void GraphicUpdate(float t) override;
	void LoadListObjectXml(char *xmlpath) ;
public:
	int Game_Init(HWND) override;
	void Game_Run(HWND, int) override;
	void Game_End(HWND) override;
	Scene1();
	~Scene1();
};
#endif

