#pragma once
#ifndef _SCENE1_H
#define _SCENE1_H
#include "game.h"
class Scene1: public Game
{
private:
	virtual void Key_Pressed(int KeyCode) override;
	virtual void InputUpdate() override;
	virtual void PhysicsUpdate() override;
	virtual void GraphicUpdate() override;
public:
	int Game_Init(HWND) override;
	void Game_Run(HWND) override;
	void Game_End(HWND) override;
	Scene1();
	~Scene1();
};
#endif

