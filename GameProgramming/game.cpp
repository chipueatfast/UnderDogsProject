#include "game.h"
#include <math.h>
#include <limits>
#include <d3dx9.h>
#include "GameTime.h"
#include "dxinput.h"

#define KEY_PRESSED(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0) 
#define KEY_UP(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)


//test sprite
LPDIRECT3DTEXTURE9 mario_image[2];
Sprite* mario;
LPDIRECT3DSURFACE9 back;

HRESULT result;


//collision check
int width, height;
int vx, vy;
D3DRECT movingRect, staticRect;
//timing variable
long start = GetTickCount();
//initializes the game
int Game::Game_Init(HWND hwnd)
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
		MessageBox(hwnd	, "Error initializing the keyboard", "Error", MB_OK);
		return 0;
	}
	mario = new Sprite("RunLeft.png", 22, 20, 4, 4);
	//load the background image
	back = LoadSurface("c.bmp", 0);
	//initialize the sprite's properties
	mario->set_x(100);
	mario->set_y(150);
	mario->set_width(21);
	mario->set_height(39);
	mario->set_curframe(0);
	mario->set_lastframe(1);
	mario->set_animdelay(2);
	mario->set_animcount(0);
	mario->set_movex(3);
	mario->set_movey(0);
	//return okay
	return 1;
}

//the main game loop
void Game::Game_Run(HWND hwnd, int delta)
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


		//"warp" the sprite at screen edges 
		if (mario->x() > SCREEN_WIDTH - mario->width()) 
		mario->set_x(0);
		if (mario->x() < 0) 
			mario->set_movex(SCREEN_WIDTH - mario->width());
		GraphicUpdate();
	}
	
	//d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, NULL);
	////start rendering
	//d3ddev->BeginScene();
	//
	//movingRect.x2 = movingRect.x1 + width;
	//movingRect.y2 = movingRect.y1 + height;
	//d3ddev->Clear(1, &movingRect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 255), 1.0f, NULL);
	//d3ddev->Clear(1, &staticRect, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, NULL);
	//d3ddev->EndScene();
	
	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);
	//check for escape key (to exit program)
	if (KEY_PRESSED(VK_ESCAPE))
		PostMessage(hwnd, WM_DESTROY, 0, 0);
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
void Game::Key_Pressed(int KeyCode)
 {
	switch (KeyCode)
	{
	case DIK_SPACE:
 		mario->set_y(mario->y() - 20);
		break;
	}
}

//loop components
void Game::InputUpdate()
{
	Poll_Keyboard();
	ProcessKeyboard();
	//check for left arrow
	if (Key_Hold(DIK_LEFT))
		mario->set_x(mario->x() - 5);
	if (Key_Hold(DIK_RIGHT))
		mario->set_x(mario->x() + 5);
}
void Game::PhysicsUpdate()
{
	float dxEntry, dxExit, txEntry, txExit;
	float dyEntry, dyExit, tyEntry, tyExit;
	float tEntry, tExit;

	if (vy == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = -std::numeric_limits<float>::infinity();
		if (staticRect.y1 > movingRect.y2 || staticRect.y2 < movingRect.y1)
		{
			movingRect.x1 += vx;			
			return;
		}
	}
	if (vx == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = -std::numeric_limits<float>::infinity();
		if (staticRect.x1 > movingRect.x2 || staticRect.x2 < movingRect.x1)
		{
			movingRect.y1 += vy;

			return;
		}
	}
		
	if (vx > 0)
	{
		//distance of near side with vx > 0
		dxEntry = staticRect.x1 - movingRect.x2;
		//distance of far side with vx > 0
		dxExit = staticRect.x2 - movingRect.x1;
		//time moving enter static
		txEntry = dxEntry / vx;
		txExit = dxExit / vx;	

	}
	if (vx < 0)
	{
		dxEntry = movingRect.x1 - staticRect.x2;
		dxExit = movingRect.x2 - staticRect.x1;

		txEntry = dxEntry / vx;
		txExit = dxExit / vx;
	}
	if (vy > 0)
	{
		//distance of near side with vx > 0
		dyEntry = staticRect.y1 - movingRect.y2;
		//distance of far side with vx > 0
		dyExit = staticRect.y2 - movingRect.y1;
		//time moving enter static
		tyEntry = dyEntry / vy;
		tyExit = dyExit / vy;	
		if (tyEntry<0)
		{
			tyEntry = 0;
			
		}
	}
	if (vy < 0)
	{
		//distance of near side with vx > 0
		dyEntry =  movingRect.y1 - staticRect.y2;
		//distance of far side with vx > 0
		dyExit = movingRect.y2 - staticRect.y1;
		//time moving enter static
		tyEntry = dyEntry / vy;
		tyExit = dyExit / vy;
		if (tyEntry>0)
		{
			tyEntry = 0;
		}
	}

	if (tyEntry != -std::numeric_limits<float>::infinity() && txEntry != -std::numeric_limits<float>::infinity())
		tEntry = max(fabs(txEntry), fabs(tyEntry));
	else tEntry = (txEntry == -std::numeric_limits<float>::infinity()) ? tyEntry : txEntry;
	if (tyExit != std::numeric_limits<float>::infinity() && txEntry != std::numeric_limits<float>::infinity())
		tExit = min(fabs(tyExit), fabs(txExit));
	else tExit = (txExit == std::numeric_limits<float>::infinity()) ? tyExit : txExit;
	if ( fabs(tEntry) <1.0f && fabs(tEntry)<fabs(tExit))
	{
		movingRect.x1 += vx*tEntry;
		movingRect.y1 += vy*tEntry;
		return;
	}
	movingRect.x1 += vx;
	movingRect.y1 += vy;
			
		
	
	
	 
}
void Game::GraphicUpdate()
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
//frees memory and cleans up before the game ends
void Game::Game_End(HWND hwnd)
{

}
