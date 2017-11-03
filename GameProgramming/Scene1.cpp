#include "Scene1.h"
#include "dxinput.h"

#define CHARACTER_VX 2
//test sprite
LPDIRECT3DTEXTURE9 mario_image[2];
Sprite* mario;
LPDIRECT3DSURFACE9 back;


HRESULT result;


////collision check
//int width, height;
//int vx, vy;
//D3DRECT movingRect, staticRect;
//timing variable
long start = GetTickCount();
//initializes the game
Scene1::Scene1()
{
}

void Scene1::Key_Pressed(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		//
	break;
	}
}

void Scene1::InputUpdate()
{
	Poll_Keyboard();
	ProcessKeyboard();
	//check for left arrow
	if (Key_Hold(DIK_LEFT));
		//mario->set_x(mario->x() - CHARACTER_VX);
		if (Key_Hold(DIK_RIGHT));
		//mario->set_x(mario->x() + CHARACTER_VX);
}

void Scene1::PhysicsUpdate()
{
	//"warp" the sprite at screen edges 
	//if (mario->x() > SCREEN_WIDTH - mario->width())
		//mario->set_x(0);
	//if (mario->x() < 0)
		//mario->set_movex(SCREEN_WIDTH - mario->width());
}

void Scene1::GraphicUpdate(float t)
{
	//has the animation delay reached threshold
	//start rendering
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
	d3ddev->BeginScene();
	//erase the entire background 
	d3ddev->StretchRect(back, NULL, backbuffer, NULL, D3DTEXF_NONE);
	//start sprite handler 
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
	character->Translation(D3DXVECTOR2(100,100));
	character->Update(t);
	//stop drawing 
	sprite_handler->End();
	//stop rendering 
	d3ddev->EndScene();
}

int Scene1::Game_Init(HWND hwnd)
{
	//initialize keyboard 
	if (!Init_Keyboard(hwnd))
	{
		MessageBox(hwnd, "Error initializing the keyboard", "Error", MB_OK);
		return 0;
	}
	character = new Aladdin();
	character->setPosition(100, 100);
	character->setAnchor(AnchorPoint::BOTTOM_MID);
	return 1;

	
}

//the main game loop content
void Scene1::Game_Run(HWND hwnd)
{
	InputUpdate();
	PhysicsUpdate();

	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;
	//this keeps the game running at a steady frame rate
	float delta = GetTickCount() - start;
	if (delta >= 1000/10
		)
	{
		//reset timing
		start = GetTickCount();
		GraphicUpdate(delta);
	}
	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);
	//check for escape key (to exit program)
	if (KEY_PRESSED(VK_ESCAPE))
		PostMessage(hwnd, WM_DESTROY, 0, 0);
}

void Scene1::Game_End(HWND)
{
}


Scene1::~Scene1()
{
}