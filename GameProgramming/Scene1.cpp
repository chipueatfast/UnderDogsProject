#include "Scene1.h"
#include "dxinput.h"


//test sprite

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
	mapinfo = new D3DXIMAGE_INFO();
}

void Scene1::Key_Pressed(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
	{
		character->setState("Idle1");
		character->Stop();
		MyCamera::GetInstance()->setVx(0);
		MyCamera::GetInstance()->Stop();
	}; break;
	case DIK_LEFT:
	{
		//character->Move(DIK_LEFT);
		//MyCamera::GetInstance()->setVx(-CHARACTER_VX);
		//MyCamera::GetInstance()->Move();
	}; break;
	case DIK_RIGHT:
	{
		//character->Move(DIK_RIGHT);
		//MyCamera::GetInstance()->setVx(CHARACTER_VX);
		//MyCamera::GetInstance()->Move();
	}; break;
	case DIK_UP:
	{
		//character->setState("IdleUp");
		//character->Stop();
	}; break;
	case DIK_DOWN:
	{
		//character->setState("IdleDown");
		//character->Stop();
	}; break;
	}
}

void Scene1::InputUpdate()
{
	Poll_Keyboard();
	ProcessKeyboard();
	bool isNoKeyHold = 1;
	//check for left arrow
	if (Key_Hold(DIK_UP))
	{
		isNoKeyHold = 0;
		character->setState("IdleUp");
		character->Stop();
		MyCamera::GetInstance()->Stop();
	};
	if (Key_Hold(DIK_DOWN))
	{
		isNoKeyHold = 0;
		character->setState("IdleDown");
		character->Stop();
		MyCamera::GetInstance()->Stop();
	}
	if (Key_Hold(DIK_LEFT))
	{
		isNoKeyHold = 0;
		character->Move(DIK_LEFT);
		MyCamera::GetInstance()->setVx(-CHARACTER_VX);
		MyCamera::GetInstance()->Move();
	}
	if (Key_Hold(DIK_RIGHT))
	{
		isNoKeyHold = 0;
		character->Move(DIK_RIGHT);
		MyCamera::GetInstance()->setVx(CHARACTER_VX);
		MyCamera::GetInstance()->Move();
	}

	if(isNoKeyHold == 1)
	{
		character->setState("Idle1");
		character->Stop();
		MyCamera::GetInstance()->Stop();
	}
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
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,0,255), 0.0f, 0);
	RECT viewRect = MyCamera::GetInstance()->View();

	d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);


	d3ddev->BeginScene();
	//erase the entire background 
	//d3ddev->StretchRect(back, NULL, backbuffer, NULL, D3DTEXF_NONE);
	//start sprite handler 
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

#pragma region MyRegion
	sprite_handler->Draw(mapETC[0], &viewRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
#pragma endregion

	character->Update(t);
	character->Render(AnchorPoint::MIDDLE, false, true, true);
	MyCamera::GetInstance()->Update(t);


#pragma region Draw map_front
	viewRect.top += mapinfo->Height / 2;
	viewRect.bottom += mapinfo->Height / 2;
	sprite_handler->Draw(mapETC[1], &viewRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
#pragma endregion

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
	character->setPosition(100, 450);
	character->setAnchor(AnchorPoint::BOTTOM_MID);
	//character->setScale(D3DXVECTOR2(2, 2));

	mapinfo = new D3DXIMAGE_INFO();
	background = LoadSurface("Res/background.png", D3DCOLOR_XRGB(63,72,204));

	mapETC[0] = LoadTexture("Res/map.png", D3DCOLOR_XRGB(63, 72, 204), mapinfo);
	mapETC[1] = LoadTexture("Res/map.png", D3DCOLOR_XRGB(63, 72, 204), mapinfo);
	MyCamera::GetInstance()->setCurMapWidth(mapinfo->Width);
	MyCamera::GetInstance()->setCurMapHeight(mapinfo->Height);

	
	//viewRect.top = _curMapHeight - SCREEN_HEIGHT/2;
	//viewRect.left = 0;
	//viewRect.bottom = viewRect.top + SCREEN_HEIGHT / 2;
	//viewRect.right = viewRect.left + SCREEN_WIDTH / 2;


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
	if (delta >= 1000/10)
	{
		//reset timing
		start = GetTickCount();
		GraphicUpdate(delta/50);
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
