#include "Scene1.h"
#include "dxinput.h"

#define CHARACTER_VX 2
//test sprite
LPDIRECT3DTEXTURE9 mario_image[2];
Sprite* mario;
LPDIRECT3DSURFACE9 back;
GameObject* character;

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
	mario->set_y(mario->y() - 20);
	break;
	}
}

void Scene1::InputUpdate()
{
	Poll_Keyboard();
	ProcessKeyboard();
	//check for left arrow
	if (Key_Hold(DIK_LEFT))
		mario->set_x(mario->x() - CHARACTER_VX);
	if (Key_Hold(DIK_RIGHT))
		mario->set_x(mario->x() + CHARACTER_VX);
}

void Scene1::PhysicsUpdate()
{
	//"warp" the sprite at screen edges 
	if (mario->x() > SCREEN_WIDTH - mario->width())
		mario->set_x(0);
	if (mario->x() < 0)
		mario->set_movex(SCREEN_WIDTH - mario->width());
}

void Scene1::GraphicUpdate()
{
	//has the animation delay reached threshold
	mario->set_animcount(mario->animcount() + 1);
	if (mario->animcount()> mario->animdelay())
	{
		//reset counter
		mario->set_animcount(0);
		//animate the sprite
		mario->Next();
	}
	//start rendering
	d3ddev->BeginScene();
	//erase the entire background 
	d3ddev->StretchRect(back, NULL, backbuffer, NULL, D3DTEXF_NONE);
	//start sprite handler 
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
	//create vector to update sprite position 
	D3DXVECTOR3 position((float)mario->x(), (float)mario->y(), 0);
	//draw the sprite 
	//sprite_handler->Draw( mario_image[mario->curframe()], NULL, NULL, &position, D3DCOLOR_XRGB(255,255,255));
	mario->Render(mario->x(), mario->y());
	//stop drawing 
	sprite_handler->End();
	//stop rendering 
	d3ddev->EndScene();
}

int Scene1::Game_Init(HWND hwnd)
{
	/*vy = 1.0f;
	vx = 1.0f;
	width = 20.0f;
	height = 20.0f;
	movingRect.x1 = 40.0f;
	movingRect.y1 = 20.0f;
	movingRect.x2 = movingRect.x1+width;
	movingRect.y2 = movingRect.y1 + height;
	staticRect.x1 = 400.0f;
	staticRect.x2 = 420.0f;
	staticRect.y1 = 0.0f;
	staticRect.y2 = 400.0f;*/
	//initialize keyboard 
	if (!Init_Keyboard(hwnd))
	{
		MessageBox(hwnd, "Error initializing the keyboard", "Error", MB_OK);
		return 0;
	}
	mario = new Sprite("RunLeft.png", 22, 20, 4, 4);
	//load the background image
	back = LoadSurface("c.bmp", 0);
	character = new GameObject();
	//initialize the sprite's properties
	mario->set_x(100);
	mario->set_y(150);
	mario->set_width(21);
	mario->set_height(39);
	mario->set_curframe(0);
	mario->set_lastframe(1);
	mario->set_animdelay(2);
	mario->set_animcount(0);
	character->setSprite(mario);
	character->setPosition(100, 150);
	//return okay
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
	if (GetTickCount() - start >= 30)
	{
		//reset timing
		start = GetTickCount();
		GraphicUpdate();
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
