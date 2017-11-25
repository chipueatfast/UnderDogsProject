#pragma once
#ifndef _UI_SCENE1_
#define _UI_SCENE1_
#include "sprite.h"

class UIScene1
{
private:
	Sprite* _healthIcon;
	RECT _healthRect;
	Sprite* _UPIcon;
	RECT _UPRect;
	Sprite* _appleIcon;
	RECT _appleRect;
	ID3DXFont* _font;
	void CalculateHealthBar(int health);
public:
	UIScene1();
	~UIScene1();
	void Render(int health);
	void RenderText(int UP, int applecount);
};

#endif
