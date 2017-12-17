#pragma once
#ifndef _SCENE1_H
#define _SCENE1_H
#include"Aladdin.h"
#include "game.h"
#include <list>
#include <d3dx9.h>
#include "UIScene1.h"

class Scene1: public Game
{
private: 
	//Disappear effect
	GameObject* _explosion;
	//Special object in scene
	GameObjectMove* _camel;
	Aladdin* mainCharacter;
	CSound* _soundJump;
	CSound* _soundSlash;
	CSound* _soundThrowApple;
	CSound* _soundCollectApple;
	CSound* _soundCamel;
	CSound* _soundSpringBoard;
	CSound* _soundAppleCollision;
	LPDIRECT3DSURFACE9 background;
	LPDIRECT3DTEXTURE9 mapETC;
	RECT viewRect; 
	//GameObject * testObject = new GameObject();//object duoi dang co xml
	//GameObject * namObject = new GameObject();//object duoi dang chi co mot hinh anh
	map<string, int> mapIdName;
	UIScene1* _UI;
	
	virtual void DisposablePhysicUpdate(float) override;
	void EnemyThinAI(GameObjectMove* obj_mov);
	void EnemyMusAI(GameObjectMove* obj_mov);
	void EnemyFatAI(GameObjectMove* obj_mov);
	void EnemyJugAI(GameObjectMove* obj_mov);
	void EnemyJarAI(GameObjectMove* obj_mov);
	void EnemyHandAI(GameObjectMove* obj_mov);
	virtual void CollisionDetect() override;
	virtual void Key_Pressed(int KeyCode) override;
	void NormalizeAction();
	virtual void InputUpdate() override;
	virtual void PhysicsUpdate(float) override;
	virtual void GraphicUpdate(float t) override;
	void EnemyHandle(float t);
	void LoadListObjectXml(char *xmlpath) ;
public:
	int Game_Init(HWND) override;
	void Game_Run(HWND, int) override;
	void Game_End(HWND) override;
	Scene1();
	~Scene1();
};
#endif

