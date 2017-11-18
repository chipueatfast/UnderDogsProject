#include "Scene1.h"
#include "dxinput.h"
#include "GameTime.h"
#include "trace.h"
#include "Quadtree.h"
#include "Camera.h"
#include "ApplePrefab.h"


#include "EnemyThinPrefab.h"
#include "EnemyMusPrefab.h"
#include "EnemyFatPrefab.h"
#include "EnemyJugPrefab.h"
#include "EnemyJarPrefab.h"

#include "RopePrefab.h"
#include "GroundPrefab.h"
#include "WallPrefab.h"
#include "HorizontalBarPrefab.h"


#include "CamelPrefab.h"


#include "FloatGroundPrefab.h"
#include "SpringBoardPrefab.h"


#define GRAVITY 0.1f
#define JUMP_FORCE -0.5f



HRESULT result;

//timing variable
DWORD start = GetTickCount();
//initializes the game
Scene1::Scene1()
{
}
int Scene1::Game_Init(HWND hwnd)
{
	//init sound files
	_gameObjectList = new list<GameObject*>();
	LoadListObjectXml("Res/Scene1XML.xml"); 
	//LoadListObjectXml("Res/AgrabahMarketMap.xml");
	mapIdName["Apple"] = 0;
	mapIdName["Ground"] = 1;
	mapIdName["Wall"] = 2;
	mapIdName["Rope"] = 3;
	mapIdName["HorizontalBar"] = 4;
	mapIdName["FloatGround"] = 5;
	mapIdName["SpringBoard"] = 6;
	mapIdName["Camel"] = 7;
	mapIdName["EnemyThin"] = 11;
	mapIdName["EnemyMus"] = 12;
	mapIdName["EnemyFat"] = 13;
	mapIdName["EnemyJug"] = 14;
	mapIdName["EnemyJar"] = 15;
#pragma region Sound
	//_soundTheme = LoadSound("Res/Audio/LifeCollect.wave");
	//_soundJump = LoadSound("Cuica-1.wave");
	//_soundSlash = LoadSound("Res/Audio/IdleDownSplash.wave");
	//_soundThrowApple = LoadSound("Res/Audio/AppleThrow.wave");
	//_soundCollectApple = LoadSound("Res/Audio/AppleCollect.wave");
	//_soundCamel = LoadSound("Res/Audio/Camel.wave");
	//_soundSpringBoard = LoadSound("Res/Audio/SpringBroad.wave");
#pragma endregion
	//if (_soundTheme == NULL)
	//	return 0;
	////_soundTheme->Play(0, DSBPLAY_LOOPING);

	//initialize keyboard 
	if (!Init_Keyboard(hwnd))
	{
		MessageBox(hwnd, "Error initializing the keyboard", "Error", MB_OK);
		return 0;
	}
	//Init components 

	 

	mapinfo = new D3DXIMAGE_INFO();
	background = LoadSurface("Res/background.png", D3DCOLOR_XRGB(63, 72, 204));
	mapETC = LoadTexture("Res/map.png", D3DCOLOR_XRGB(63, 72, 204), mapinfo);

	mainCharacter = new Aladdin();
	mainCharacter->setAnchor(AnchorPoint::BOTTOM_MID);
	mainCharacter->setPosition(100, 400);

	MyCamera::GetInstance()->setCurMapWidth(mapinfo->Width);
	MyCamera::GetInstance()->setCurMapHeight(mapinfo->Height);
	MyCamera::GetInstance()->setPosition(MyCamera::GetInstance()->width()/2, mapinfo->Height / 2 - MyCamera::GetInstance()->height()/2);
	//return okay
	return 1;

}

void Scene1::Key_Pressed(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		PlaySound(_soundJump);
		break;
	case DIK_X:
		mainCharacter->set_hand_state("2");
		break;
	case DIK_C:
		mainCharacter->set_hand_state("1");
		mainCharacter->FireApple();
		break;
	case DIK_Z:
		if (mainCharacter->sub_state() != "1" && mainCharacter->sub_state() != "2")
		{
			mainCharacter->set_sub_state("2");
			mainCharacter->set_vy(JUMP_FORCE);
		}
		break;

	}
}

void Scene1::InputUpdate()
{
	Poll_Keyboard();
	ProcessKeyboard();
	if (Key_Hold(DIK_UP))
	{
		mainCharacter->set_main_state("2");
		mainCharacter->Stop();
		MyCamera::GetInstance()->Stop();
		return;
	};
	if (Key_Hold(DIK_DOWN))
	{
		mainCharacter->Stop();
		MyCamera::GetInstance()->Stop();
		mainCharacter->set_main_state("3");
		return;
	}
	if (Key_Hold(DIK_LEFT))
	{
		mainCharacter->set_main_state("1");
		mainCharacter->set_vx(-CHARACTER_VX);
		MyCamera::GetInstance()->setVx(mainCharacter->vx());
		return;
	}
	if (Key_Hold(DIK_RIGHT))
	{
		mainCharacter->set_main_state("1");
		mainCharacter->set_vx(CHARACTER_VX);
		MyCamera::GetInstance()->setVx(mainCharacter->vx());
		return;
	}
	if (Key_Hold(DIK_Z))
	{
		return;
	}
	mainCharacter->set_main_state("0");
	mainCharacter->Stop();
	MyCamera::GetInstance()->Stop();

	return;


}

void Scene1::CollisionDetect()
{

	Quadtree* quadtree = Quadtree::CreateQuadtree(MyCamera::GetInstance()->View().left, MyCamera::GetInstance()->View().top, mapinfo->Width, mapinfo->Height/2);
	std::list<GameObject*>* return_object_list = new std::list<GameObject*>();
	quadtree->Retrieve(return_object_list, mainCharacter);
	for (auto x = return_object_list->begin(); x != return_object_list->end(); x++)
	//for(auto x = _gameObjectList->begin(); x != _gameObjectList->end();x++)
	{

		GameObject *temp_obj = *x;
		mainCharacter->set_bounding_box(CalculateBoundingBox(mainCharacter->x(), mainCharacter->y(), mainCharacter->width(), mainCharacter->height(), mainCharacter->anchor()));
		temp_obj->set_bounding_box(CalculateBoundingBox(temp_obj->x(), temp_obj->y(), temp_obj->width(), temp_obj->height(), temp_obj->anchor()));


		CollisionResult collisionResult = CheckCollision(mainCharacter, temp_obj);

	
		if (collisionResult._collisionIndex < 1 && collisionResult._collisionIndex >= 0)
		{
			if (temp_obj->get_name() == "Wall")
			{
				if (collisionResult._collisionSide == LEFT)
				{
					mainCharacter->set_vx(0);
					MyCamera::GetInstance()->setVx(0);
					mainCharacter->setPosition(mainCharacter->x() - 1, mainCharacter->y());
					MyCamera::GetInstance()->setPosition(D3DXVECTOR3(MyCamera::GetInstance()->Position().x - 1, MyCamera::GetInstance()->Position().y, 0));
					mainCharacter->set_sub_state("3");
				}
				if (collisionResult._collisionSide == RIGHT)
				{
					mainCharacter->set_vx(0);
					MyCamera::GetInstance()->setVx(0);
					mainCharacter->setPosition(mainCharacter->x() + 1, mainCharacter->y());
					MyCamera::GetInstance()->setPosition(D3DXVECTOR3(MyCamera::GetInstance()->Position().x + 1, MyCamera::GetInstance()->Position().y, 0));
					mainCharacter->set_sub_state("3");
				}
			}
			if (temp_obj->get_name() == "Ground")
			{
				if (collisionResult._collisionSide == DOWN)
				{
					//trace(L"Index: %f", collisionIndex);
					mainCharacter->set_vy((-collisionResult._collisionIndex*mainCharacter->vy()));
				}
				if (collisionResult._collisionSide == UP)
				{
					mainCharacter->set_vy((collisionResult._collisionIndex*mainCharacter->vy()));
				}
				if(collisionResult._collisionSide== LEFT || collisionResult._collisionSide==RIGHT)
				{
						mainCharacter->set_vx(0);
				}
			}

			if (temp_obj->get_name() == "Apple")
			{
				//collectApple & clear this apple from list
				
				//sound
				//_soundCollectApple->Play();
				
			}

			if (temp_obj->get_name() == "EnemyFat" || temp_obj->get_name() == "EnemyJug" || temp_obj->get_name() == "EnemyHand" || temp_obj->get_name() == "EnemyMus" || temp_obj->get_name() == "EnemyThin")
			{
				//- health of aladdin  
				mainCharacter->BeHitted();

				// sound
			}
			if (temp_obj->get_name() == "Camel" && mainCharacter->sub_state() == "2" && collisionResult._collisionSide == DOWN)
			{
				//event 
				//temp_obj->set_state("CamelBeaten");
				//sound
				//_soundCamel->Play();
			}
			if (temp_obj->get_name() == "SpringBoard")
			{
				if (collisionResult._collisionSide == UP)
				{
					mainCharacter->set_sub_state("2");
					mainCharacter->set_vy(JUMP_FORCE);
				}

				//_soundSpringBoard->Play();
			}
#pragma region Test

			LPCSTR side = LPCSTR();
			switch (collisionResult._collisionSide)
			{
			case LEFT:
			{
				side = "LEFT";
			}; break;
			case RIGHT:
			{
				side = "RIGHT";
			}; break;
			case UP:
			{
				side = "UP";
			}; break;
			case DOWN:
			{
				side = "DOWN";
			}; break;
			case NONE:
			{
				side = "NONE";
			}; break;
			}

			if (side != "UP")
			{
				OutputDebugString("\n");
				OutputDebugString(side);
			}
			//PlaySound(_soundJump);
#pragma endregion
			for (list<AppleBullet*>::iterator ab = mainCharacter->bullet_list()->begin(); ab != mainCharacter->bullet_list()->end(); ab++)
			{
				quadtree->Retrieve(return_object_list, *ab);
				for (list<GameObject*>::iterator g = return_object_list->begin(); g != return_object_list->end(); g++)
				{
					auto surfaceVector = new D3DVECTOR();
					CollisionResult collisionIndex = CheckCollision(*ab, *g);
					AppleBullet* temp_obj = *ab;
					if (collisionIndex._collisionIndex<1.0f && collisionIndex._collisionIndex > 0.0f)
					{
						
						temp_obj->set_vx(collisionIndex._collisionIndex * temp_obj->vx());
						temp_obj->set_vy(collisionIndex._collisionIndex * temp_obj->vy());
						
						break;
					}
					if (collisionIndex._collisionIndex == 0.0f)
					{
						temp_obj->set_is_popping(true);
						temp_obj->state_manager()->setState("001");
						temp_obj->set_vx(0);
						temp_obj->set_vy(0);				
					}
				}
			}

		}
	

	}



}
void Scene1::PhysicsUpdate(float t)
{
	mainCharacter->set_vy(mainCharacter->vy() + GRAVITY);

	if (mainCharacter->vy() == GRAVITY)
	{
		mainCharacter->set_sub_state("0");
	}

	CollisionDetect();
	mainCharacter->setState(mainCharacter->main_state() + mainCharacter->sub_state() + mainCharacter->hand_state());
	if (mainCharacter->vx() != 0)
	{
		if (mainCharacter->vx() > 0)
		{
			mainCharacter->set_curFace(GameObject::Face::RIGHT);
		}
		else
		{
			mainCharacter->set_curFace(GameObject::Face::LEFT);
		}
		if (mainCharacter->CheckFlip())
			mainCharacter->Flip();
	}

	mainCharacter->PhysicUpdate(t);

}

void Scene1::GraphicUpdate(float t)
{
	//Real Graphics Update
	for (auto i = _gameObjectList->begin(); i != _gameObjectList->end(); i++)
	{
		GameObject* temp_object = *i;
		temp_object->GraphicUpdate(t);
	}
	mainCharacter->GraphicUpdate(t);
	  
	MyCamera::GetInstance()->Update(t);


	//Render Everything
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);

	viewRect = MyCamera::GetInstance()->View();
	d3ddev->BeginScene();
	 //erase the entire background 
	//d3ddev->StretchRect(back, NULL, backbuffer, NULL, D3DTEXF_NONE);
	//start sprite handler 	
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

	sprite_handler->SetTransform(&old_matrix);
	sprite_handler->Draw(mapETC, &viewRect,NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));


	mainCharacter->Render(false, true, true);
	mainCharacter->DrawBullet();
	list<GameObject*>* visibleList = OnScreenDetect();

	for (auto i = visibleList->begin(); i != visibleList->end(); i++)
	{
		GameObject* temp_object = *i;
		temp_object->setAnchor(AnchorPoint::BOTTOM_MID);
		temp_object->setTranslation(D3DXVECTOR2(temp_object->x() - viewRect.left, temp_object->y() - viewRect.top));
		temp_object->Render();
		//temp_object->RenderBounding(D3DCOLOR_ARGB(200, 255, 0, 0));
	}
	delete visibleList;
	 

#pragma region Draw map_front
	viewRect.top += mapinfo->Height / 2;
	viewRect.bottom += mapinfo->Height / 2;
	sprite_handler->SetTransform(&old_matrix);
	sprite_handler->Draw(mapETC, &viewRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	
#pragma endregion

	//mainCharacter->RenderBounding(D3DCOLOR_ARGB(150, 0, 250, 0));
	sprite_handler->End();
	//stop rendering 
	d3ddev->EndScene();



}


void Scene1::LoadListObjectXml(char* xmlpath)
{

	xml_document fileXml;
	xml_parse_result result = fileXml.load_file(xmlpath);
	xml_node root = fileXml.child("map");

	map<string, char* > mapSpritePath;
	//map<string, char*> mapStatePath;

	for (xml_node node : root.children("tileset"))
	{
		//add mapSprite elements
		string name = node.attribute("name").value();

		string pathSprite = node.child("image").attribute("source").value();
		char* cPathSprite = new char[pathSprite.length() + 1];
		memcpy(cPathSprite, pathSprite.c_str(), pathSprite.length() + 1);
		mapSpritePath[name] = cPathSprite;

		//add mapState elements
		string pathState = node.child("statexml").attribute("source").value();
		/*if (pathState != "")
		{
		char* cPathState = new char[pathState.length() + 1];
		memcpy(cPathState, pathState.c_str(), pathState.length() + 1);
		mapStatePath[name] = cPathState;
		} */
	}


	for (xml_node node : root.children("objectgroup"))
	{
		map<int, string> mapName;


		string name = node.attribute("name").value();
		char* objectName = new char[name.length() + 1];
		memcpy(objectName, name.c_str(), name.length() + 1);

		int idName = atoi(node.attribute("id").value());



		//check if pathSprite constained  in map
		string pathSprite = "";
		if (mapSpritePath.count(name) != 0)
			pathSprite = mapSpritePath[name];
		char* cPathSprite = new char[pathSprite.length() + 1];
		memcpy(cPathSprite, pathSprite.c_str(), pathSprite.length() + 1);




		float anchorTransformX = 0;
		float anchorTransformY = 0;
		//string face = node.attribute("face").value();
		for (xml_node object = node.first_child(); object; object = object.next_sibling())
		{

			if (name == "Ground" || name == "HorizontalBar" || name == "Rope" || name == "Wall")
			{
				anchorTransformY = atoi(object.attribute("height").value());
			}
			anchorTransformX = atoi(object.attribute("width").value()) / 2;

			GameObject * anObject;
			switch (idName)
			{
			case 0:
				anObject = new GameObject();
				ApplePrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 1:
				anObject = new GameObject();
				GroundPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 2:
				anObject = new GameObject();
				WallPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 3:
				anObject = new GameObject();
				RopePrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 4:
				anObject = new GameObject();
				HorizontalBarPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 5:
				anObject = new GameObject();
				FloatGroundPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 6:
				anObject = new GameObject();
				SpringBoardPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 7:
				anObject = new GameObject();
				CamelPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 11:
				anObject = new GameObjectMove();
				EnemyThinPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 12:
				anObject = new GameObjectMove();
				EnemyMusPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 13:
				anObject = new GameObjectMove();
				EnemyFatPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 14:
				anObject = new GameObjectMove();
				EnemyJugPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			case 15:
				anObject = new GameObjectMove();
				EnemyJarPrefab::Instantiate(anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				break;
			default:
				anObject = new GameObject();

			}
			anObject->setAnchor(AnchorPoint::BOTTOM_MID);
			anObject->set_bounding_box(CalculateBoundingBox(anObject->x(), anObject->y(), anObject->width(), anObject->height(), anObject->anchor()));

			_gameObjectList->push_back(anObject);
		}
	}
}


//the main game loop content
void Scene1::Game_Run(HWND hwnd, int dt)
{
	GameTime::GetInstance()->StartCounter();
	InputUpdate();

	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;
	DWORD now = GetTickCount();
	//this keeps the game running at a steady frame rate
	float t = now - start;
	if (t >= 1000 / FPS)
	{
		//reset timing
		start = now;
		if (t < FIXED_TIME)
			Sleep(100 - FIXED_TIME);
		PhysicsUpdate(FIXED_TIME);
		GraphicUpdate(FIXED_TIME);
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