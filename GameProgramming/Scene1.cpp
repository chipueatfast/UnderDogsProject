#include "Scene1.h"
#include "dxinput.h"
#include "GameTime.h"

#define CHARACTER_VX 3
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
	//mario->set_y(mario->y() - 20);
	PlaySound(_soundJump);
	break;
	}
}

void Scene1::InputUpdate()
{
	Poll_Keyboard();
	ProcessKeyboard();
	//check for left arrow
	//if (Key_Hold(DIK_LEFT))
	//	/*mario->set_x(mario->x() - CHARACTER_VX);*/
	if (Key_Hold(DIK_LEFT))
	{
		mainCharacter->set_vx(-CHARACTER_VX);
		mainCharacter->setPosition(mainCharacter->x() + mainCharacter->vx(), mainCharacter->y());
		return;
	}
	if (Key_Hold(DIK_RIGHT))
	{
		mainCharacter->set_vx(CHARACTER_VX);
		mainCharacter->setPosition(mainCharacter->x() + mainCharacter->vx(), mainCharacter->y());	
		return;
	}
	mainCharacter->set_vx(0);
}

void Scene1::PhysicsUpdate()
{
	if (mainCharacter->vx() > 0)
		mainCharacter->setState("Running");
	if (mainCharacter->vx() < 0)
	{
		mainCharacter->setState("Running");
		//mainCharacter->Flip();
	}
	if (mainCharacter->vx()==0)
		mainCharacter->setState("Idle1");

}

void Scene1::GraphicUpdate(float t)
{
	mainCharacter->Update(t);
	d3ddev->BeginScene();
	//erase the entire background 
	d3ddev->StretchRect(back, NULL, backbuffer, NULL, D3DTEXF_NONE);
	//start sprite handler 
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0),1.0f, 0);
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

	//load animation, cap nhat lai anchor point theo frame
	mainCharacter->Translation(D3DXVECTOR2(mainCharacter->x(), mainCharacter->y()));

	sprite_handler->End();
	//stop rendering 
	d3ddev->EndScene();
}

int Scene1::Game_Init(HWND hwnd)
{
	//init sound files
	_soundTheme = LoadSound("alarm_beep.WAVE");
	_soundJump = LoadSound("Cuica-1.wave");
	if (_soundTheme == NULL)
		return 0;
	_soundTheme->Play(0, DSBPLAY_LOOPING);
	//initialize keyboard 
	if (!Init_Keyboard(hwnd))
	{
		MessageBox(hwnd, "Error initializing the keyboard", "Error", MB_OK);
		return 0;
	}	
	mainCharacter = new Aladdin();
	mainCharacter->setAnchor(AnchorPoint::BOTTOM_MID);
	mainCharacter->setPosition(100, 150);
	mainCharacter->set_animadelay(85);
	
	

	//return okay
	return 1;

	
}

//the main game loop content
void Scene1::Game_Run(HWND hwnd, int dt)
{
	GameTime::GetInstance()->StartCounter();
	InputUpdate();
	PhysicsUpdate();
	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;
	//this keeps the game running at a steady frame rate
	float t = GetTickCount() - start;
	if (t >= 1000/15)
	{
		//reset timing
		start = GetTickCount();
		GraphicUpdate(t);
	}
	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);
	//check for escape key (to exit program)
	if (KEY_PRESSED(VK_ESCAPE))
		PostMessage(hwnd, WM_DESTROY, 0, 0);
	Sleep(6 - GameTime::GetInstance()->GetCounter());
}

void Scene1::Game_End(HWND)
{



}


Scene1::~Scene1()
{
}
