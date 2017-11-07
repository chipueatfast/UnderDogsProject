#include "Scene1.h"
#include "dxinput.h"
#include "GameTime.h"
#include "trace.h"
#include "Quadtree.h"
#include "GameObjectList1.h"
#include "Camera.h"

#define CHARACTER_VX 1
#define GRAVITY 0

LPDIRECT3DSURFACE9 back;
GameObject* character;
//GameObject* ground;

HRESULT result;



//timing variable
long start = GetTickCount();
//initializes the game
Scene1::Scene1()
{
}
int Scene1::Game_Init(HWND hwnd)
{
	//init sound files
	
	_soundTheme = LoadSound("alarm_beep.WAVE");
	_soundJump = LoadSound("Cuica-1.wave");
	if (_soundTheme == NULL)
		return 0;
	//_soundTheme->Play(0, DSBPLAY_LOOPING);
	//initialize keyboard 
	if (!Init_Keyboard(hwnd))
	{
		MessageBox(hwnd, "Error initializing the keyboard", "Error", MB_OK);
		return 0;
	}	
	//Init components

	mainCharacter = new Aladdin();
	mainCharacter->setAnchor(AnchorPoint::BOTTOM_MID);
	mainCharacter->setPosition(100, 450);
	GameObjectList1::GetInstance()->Add(mainCharacter);

	mapinfo = new D3DXIMAGE_INFO();
	background = LoadSurface("Res/background.png", D3DCOLOR_XRGB(63, 72, 204));

	mapETC[0] = LoadTexture("Res/map.png", D3DCOLOR_XRGB(63, 72, 204), mapinfo);
	mapETC[1] = LoadTexture("Res/map.png", D3DCOLOR_XRGB(63, 72, 204), mapinfo);
	MyCamera::GetInstance()->setCurMapWidth(mapinfo->Width);
	MyCamera::GetInstance()->setCurMapHeight(mapinfo->Height);

	//Sprite* sprite_ground;
	//sprite_ground = new Sprite("ground.png", 890, 250);
	/*ground = new GameObject();
	
	ground->setPosition(0, 300);
	ground->setAnchor(TOP_LEFT);
	ground->setSprite(sprite_ground);
	GameObjectList1::GetInstance()->Add(ground);*/

	
	
	

	//return okay
	return 1;

	
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
	if (Key_Hold(DIK_UP))
	{
		//isNoKeyHold = 0;
		mainCharacter->setState("IdleUp");
		mainCharacter->Stop();
		MyCamera::GetInstance()->Stop();
	};
	if (Key_Hold(DIK_DOWN))
	{
		//isNoKeyHold = 0;
		mainCharacter->setState("IdleDown");
		mainCharacter->Stop();
		MyCamera::GetInstance()->Stop();
	}
	if (Key_Hold(DIK_LEFT))
	{
		mainCharacter->set_vx(-CHARACTER_VX);
		mainCharacter->setPosition(mainCharacter->x() + mainCharacter->vx(), mainCharacter->y());
		MyCamera::GetInstance()->setVx(-CHARACTER_VX);
		MyCamera::GetInstance()->Move();
		return;
	}
	if (Key_Hold(DIK_RIGHT))
	{
		mainCharacter->set_vx(CHARACTER_VX);
		mainCharacter->setPosition(mainCharacter->x() + mainCharacter->vx(), mainCharacter->y());	
		MyCamera::GetInstance()->setVx(CHARACTER_VX);
		MyCamera::GetInstance()->Move();
		return;
	}
	mainCharacter->set_vx(0);
}

void Scene1::CollisionDetect(int width, int height)
{
	Quadtree* quadtree = Quadtree::CreateQuadtree(width, height);

	std::list<GameObject*>* return_object_list = new std::list<GameObject*>();
	std::list<GameObject*>* GO_list = GameObjectList1::GetInstance()->GetGOList();
	std::list<CollisionPair*>* CP_list = new list<CollisionPair*>();
	bool havCollide = false;
	//for (list<GameObject*>::iterator i = GO_list->begin(); i != GO_list->end(); i++)
	//{
	//	//Get all objects that can collide  with current entity
	//	GameObject* temp_move = *i;
	//	*i 
		quadtree->Retrieve(return_object_list, mainCharacter);
		for (auto x = return_object_list->begin(); x != return_object_list->end(); x++)
		{
			/*CollisionPair* temp_cp = new CollisionPair(mainCharacter, *x);
			if (CP_list->size() == 0)
				CP_list->push_back(new CollisionPair(mainCharacter, *x));
			for (list<CollisionPair*>::iterator p = CP_list->begin(); p!= CP_list->end(); p++)
				if (!CollisionPair::IsIndentical(*p, temp_cp))
					CP_list->push_back(new CollisionPair(mainCharacter, *x));
			delete temp_cp;*/
			float collisionIndex = CheckCollision(mainCharacter, *x);
			if (collisionIndex < 1 && collisionIndex >= 0)
			{
				mainCharacter->setPosition(mainCharacter->x(), mainCharacter->y() + mainCharacter->vy()* collisionIndex);
				havCollide = true;
			}
		}
		if (havCollide==false)
			mainCharacter->setPosition(mainCharacter->x(), mainCharacter->y() + mainCharacter->vy());
		delete CP_list;
	//}

}
void Scene1::PhysicsUpdate()
{
	mainCharacter->set_vy(GRAVITY);
	if (mainCharacter->vx() > 0)
		mainCharacter->setState("Running");
	if (mainCharacter->vx() < 0)
	{
		mainCharacter->setState("Running");
		//mainCharacter->Flip();
	}
	if (mainCharacter->vx()==0)
		mainCharacter->setState("Idle1");
	/*float gravityCheck = CheckCollision(mainCharacter, ground);
	mainCharacter->setPosition(mainCharacter->x(), mainCharacter->y() + mainCharacter->vy()*gravityCheck);*/
	CollisionDetect(640, 460);
}

void Scene1::GraphicUpdate(float t)
{
	mainCharacter->Update(t);
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);
	viewRect = MyCamera::GetInstance()->View();
	d3ddev->BeginScene();
	//back = LoadSurface("c.bmp", D3DCOLOR_XRGB(0, 0, 0));
	//erase the entire background 
	d3ddev->StretchRect(back, NULL, backbuffer, NULL, D3DTEXF_NONE);
	//start sprite handler 
	
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
	sprite_handler->Draw(mapETC[0], &viewRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//load animation, cap nhat lai anchor point theo frame
	mainCharacter->Render(MIDDLE);
	MyCamera::GetInstance()->Update(t);
	/*ground->Render();*/
#pragma region Draw map_front
	viewRect.top += mapinfo->Height / 2;
	viewRect.bottom += mapinfo->Height / 2;
	sprite_handler->Draw(mapETC[1], &viewRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
#pragma endregion

	sprite_handler->End();
	//stop rendering 
	d3ddev->EndScene();
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
