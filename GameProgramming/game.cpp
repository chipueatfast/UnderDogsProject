#include "game.h"
#include <math.h>
#include <limits>
#include <d3dx9.h>
#include "GameTime.h"
#include "dxinput.h"
#include "Camera.h"


#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)



//initializes the game
int Game::Game_Init(HWND hwnd)
{

	return 1;
}

//the main game loop
void Game::Game_Run(HWND hwnd, int dt)
{
	
	
}

//because different scene will required different action so key_pressed is protected
void Game::ProcessKeyboard()
{
	//Collect all buffered events 
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	if (dikeyboard!=nullptr)
		HRESULT hr = dikeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);
	//Scan through all data, check if the is pressed or released 
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			Key_Pressed(KeyCode);

	}
}


list<GameObject*>* Game::OnScreenDetect()
{
	Quadtree* quadtree = Quadtree::CreateQuadtree(0, 0,mapinfo->Width, mapinfo->Height/2);
	list<GameObject*>* return_object_list = new list<GameObject*>();
	quadtree->Retrieve(return_object_list, MyCamera::GetInstance());
	return return_object_list;
	
	
}

void Game::DisposablePhysicUpdate(float)
{
}


void Game::CollisionDetect()
{
}

void Game::Key_Pressed(int KeyCode)
{
	
}

//loop components
void Game::InputUpdate()
{
	
}
void Game::PhysicsUpdate(float t)
{
	
	
	
	 
}
void Game::GraphicUpdate(float t)
{
	
}

Game::Game()
{
}

//frees memory and cleans up before the game ends
void Game::Game_End(HWND hwnd)
{

}
