#ifndef _GAME_H
#define _GAME_H
#include <d3d9.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "dxgraphics.h"
#include "dxaudio.h"
#include "sprite.h"
#include "AABB.h"
#include "GameObject.h"

//application title
#define APPTITLE "FrameworkStage"
//screen setup
#define FULLSCREEN 0
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
//macros to read the keyboard asynchronously
#define KEY_PRESSED(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0) 
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
//function prototypes
class Game
{
protected:
	CSound* _soundTheme;

	void ProcessKeyboard(); //for making action by pressing (not hold) button, a part of input update
	virtual void Key_Pressed(int KeyCode);
	virtual void InputUpdate();
	virtual void PhysicsUpdate();
	virtual void GraphicUpdate();
public:
	int virtual Game_Init(HWND);
	void virtual Game_Run(HWND, int);
	void virtual Game_End(HWND);
	
};
#endif