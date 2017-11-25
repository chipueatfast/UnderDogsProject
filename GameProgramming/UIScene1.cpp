#include "UIScene1.h"
#include "dxgraphics.h"
#include "game.h"
#define MAX_HEALTH 10

void UIScene1::CalculateHealthBar(int health)
{
	_healthRect.top = 0;
	_healthRect.bottom = _healthIcon->height();
	_healthRect.left = 0;
	_healthRect.right = 50 + ((float)health / MAX_HEALTH)*(_healthIcon->width() - 50);
}

UIScene1::UIScene1()
{
	_healthIcon = new Sprite("Res/healthIcon.png", 150, 50);
	_UPIcon = new Sprite("Res/UPicon.png", 50, 50);
	_appleIcon = new Sprite("Res/appleIcon.png", 50, 50);
	_UPRect.top = SCREEN_HEIGHT*0.9 ;
	_UPRect.left = 100;
	_UPRect.bottom = _UPRect.top + 100;
	_UPRect.right = 150;

	_appleRect.top = SCREEN_HEIGHT*0.9 ;
	_appleRect.left = SCREEN_WIDTH*0.92 ;
	_appleRect.bottom = _appleRect.top + 100;
	_appleRect.right = _appleRect.left + 150;
	;
	_font = NULL;
	AddFontResource("Res/Font/Revengeance.otf");
	D3DXCreateFont(d3ddev, 30, 30, FW_LIGHT, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS
		, ANTIALIASED_QUALITY, FF_DONTCARE, "Revengeance",&_font);

}
void UIScene1::Render(int health)
{
	sprite_handler->SetTransform(&old_matrix);
	CalculateHealthBar(health);
	sprite_handler->Draw(_healthIcon->image(), &_healthRect, NULL, new D3DXVECTOR3(20, 20, 0), D3DCOLOR_XRGB(255, 255, 255));
	sprite_handler->Draw(_UPIcon->image(), NULL, NULL, new D3DXVECTOR3(20, SCREEN_HEIGHT*0.85/SCALE_RATE , 0), D3DCOLOR_XRGB(255, 255, 255));
	sprite_handler->Draw(_appleIcon->image(), NULL, NULL, new D3DXVECTOR3(SCREEN_WIDTH*0.85 / SCALE_RATE, SCREEN_HEIGHT*0.9 / SCALE_RATE, 0), D3DCOLOR_XRGB(255, 255, 255));
	
}

void UIScene1::RenderText(int UP, int applecount)
{
	if (_font)
	{
		_font->DrawTextA(NULL, to_string(UP).c_str(), -1, &_UPRect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
		_font->DrawTextA(NULL, to_string(applecount).c_str(), -1, &_appleRect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	}
}

UIScene1::~UIScene1()
{
}
