#include "Scene2.h"
#include "JafarPrefab.h"
#include "GameTime.h"
#include "dxinput.h"
#include "StarBulletPrefab.h"
#include "trace.h"
#include "FireBulletPrefab.h"
#include "ApplePrefab.h"
#include "GroundPrefab.h"
#include "WallPrefab.h"

#define JUMPFORCE_SCENE2 -31
#define GRAVITY_SCENE2 5
//for allocating purpose
bool bulletCollideScene2;
GameObject* temp_star;
GameObject* temp_object_scene2;
GameObject* temp_bullet_scene2;
AppleBullet* temp_apple_bullet_scene2;
bool drawOneOnAnime;
//timing variable
DWORD startScene2 = GetTickCount();
int Scene2::Game_Init(HWND hwnd)
{
	//init background and camera procedure
	mapinfo = new D3DXIMAGE_INFO();
	
	mapETC = LoadTexture("Res/SceneBoss/backgroundJafarfronttest.png", D3DCOLOR_XRGB(63, 72, 204), mapinfo);
	background = LoadSurface("Res/SceneBoss/backgroundJafar.png", D3DCOLOR_XRGB(63, 72, 204));
	MyCamera::GetInstance()->setCurMapWidth(mapinfo->Width);
	MyCamera::GetInstance()->setCurMapHeight(mapinfo->Height * 2);
	//init components game objects
	drawOneOnAnime = false;
	_gameObjectList = new list<GameObject*>();
	_onScreenList = new list<GameObject*>();
	_disposableList = new list<GameObject*>();
	_enemyBulletStarList = new list<GameObject*>();
	_enemyBulletFireList = new list<GameObject*>();
	LoadListObjectXml("Res/Scene2XML.xml");
	mapIdName["Ground"] = 1;
	mapIdName["Wall"] = 2;
	mapIdName["Pedestal"] = 3;
	mapIdName["StarBullet"] = 99;
	mapIdName["FireLand"] = 100;
	mapIdName["Jafar"] = 101;
	_Jafar = new GameObjectMove();
	JafarPrefab::Instantiate(_Jafar, 300, 300);
	_gameObjectList->push_back(_Jafar);
	_mainCharacter = new Aladdin();
	_mainCharacter->setAnchor(AnchorPoint::BOTTOM_MID);
	_mainCharacter->set_state("000");
	_mainCharacter->setPosition(150, 335);
	MyCamera::GetInstance()->setPosition(150, 335);

	//MyCamera::GetInstance()->setPosition(100, 521);
	//Init components 
	_UI = new UIScene();
#pragma region Sound
	_soundTheme = LoadSound("Res/Audio/LifeCollect.wave");
	_soundJump = LoadSound("Cuica-1.wave");
	_soundSlash = LoadSound("Res/Audio/IdleDownSplash.wave");
	_soundCollectApple = LoadSound("Res/Audio/AppleCollect.wave");
	_soundAppleCollision = LoadSound("Res/Audio/AppleThrowCollision.wave");
#pragma endregion
}



void Scene2::CollisionDetect()
{
	for (list<GameObject*>::iterator obj = _onScreenList->begin(); obj != _onScreenList->end(); obj++)
	{
		//Process sword 
		temp_object_scene2 = *obj;
		for (auto ab = _mainCharacter->bullet_list()->begin(); ab != _mainCharacter->bullet_list()->end(); ab++)
		{

			temp_apple_bullet_scene2 = *ab;
			if (temp_apple_bullet_scene2->Visbile() == true)
			{
				CollisionResult collisionIndex = CheckCollision(*ab, *obj);
				if (collisionIndex._collisionIndex<1.0f && collisionIndex._collisionIndex > 0.0f)
				{

					temp_apple_bullet_scene2->set_vx(collisionIndex._collisionIndex * temp_apple_bullet_scene2->vx());
					temp_apple_bullet_scene2->set_vy(collisionIndex._collisionIndex * temp_apple_bullet_scene2->vy());
					break;
				}
				if (collisionIndex._collisionIndex == 0.0f)
				{
					temp_apple_bullet_scene2->set_is_popping(true);
					temp_apple_bullet_scene2->state_manager()->setState("001");
					temp_apple_bullet_scene2->set_vx(0);
					temp_apple_bullet_scene2->set_vy(0);
					temp_object_scene2 = (GameObjectMove*)*obj;
					_soundAppleCollision->Play();
					switch (mapIdName[temp_object_scene2->get_name()])
					{
					case 101:
						if (_Jafar->is_immune() == 0.0f)
						{
							_Jafar->set_health(_Jafar->health() - 1);
							_Jafar->set_is_immune(30);
						}
						break;

					}
				}

			}
			temp_apple_bullet_scene2 = *ab;

		}


	}
	if (SimpleIntersect(_mainCharacter->sword(), &_Jafar->bounding_box()))
	{
		if (_Jafar->is_immune() == 0.0f)
		{
			_Jafar->set_health(_Jafar->health() - 1);
			_Jafar->set_is_immune(30);
			_Jafar->set_state("003");
			_Jafar->set_hand_state("3");
			_Jafar->setIsRepeating(false);
		}
	}

}
void Scene2::NormalizeAction()
{
	if (_mainCharacter->on_state_end() == true)
		_mainCharacter->set_on_state_end(false);
	_mainCharacter->set_degree_state("0");
}

void Scene2::Key_Pressed(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_U:
		_mainCharacter->set_health(_mainCharacter->health() + 1);
		break;
	case DIK_I:
		_mainCharacter->set_health(_mainCharacter->health() - 1);
		break;
	case DIK_SPACE:
		PlaySound(_soundJump);
		break;
	case DIK_X:
		NormalizeAction();
		_mainCharacter->set_hand_state("2");
		_soundSlash->Play();
		break;
	case DIK_C:
		NormalizeAction();
		if (_mainCharacter->is_throwing() == false)
		{
			_mainCharacter->set_hand_state("1");
			_mainCharacter->FireApple();
		}

		break;
	case DIK_Z:
		NormalizeAction();
		if (_mainCharacter->main_state()!="3" && _mainCharacter->sub_state()=="0")
		{
			_mainCharacter->set_sub_state("2");
			//_mainCharacter->setIsRepeating(false);
			_mainCharacter->setIsClimbing(false);
			_mainCharacter->set_vy(JUMPFORCE_SCENE2);
		}
		else
		{
			if (_mainCharacter->sub_state() == "5")
				_mainCharacter->setIsSwinging(false);
		}
		break;
	}
}

void Scene2::InputUpdate()
{

	Poll_Keyboard();
	ProcessKeyboard();

	if (Key_Hold(DIK_UP))
	{
		NormalizeAction();
		if (_mainCharacter->main_state() == "4")
		{
			_mainCharacter->set_vy(-CHARACTER_VX);
			return;
		}

		_mainCharacter->set_main_state("2");
		_mainCharacter->StopX();
		return;

	};

	if (Key_Hold(DIK_DOWN))
	{
		NormalizeAction();
		if (_mainCharacter->main_state() == "4")
		{
			_mainCharacter->set_vy(CHARACTER_VX);
			return;
		}
		_mainCharacter->StopX();
		_mainCharacter->set_main_state("3");
		return;
	}

	if (Key_Hold(DIK_LEFT))
	{
		NormalizeAction();
		if (_mainCharacter->main_state() != "4")
		{
			if (_mainCharacter->on_state_end() == true)
				_mainCharacter->set_on_state_end(false);
			_mainCharacter->set_main_state("1");

			if (_mainCharacter->main_state() == "1")
			{
				if (_mainCharacter->on_state_end() == false)
					_mainCharacter->set_prev_main_state("1");
			}
		}

		if (_mainCharacter->isClimbing() == false)
			_mainCharacter->set_vx(-CHARACTER_VX);
		else
			_mainCharacter->set_vx(0);
		return;
	}
	if (Key_Hold(DIK_RIGHT))
	{
		NormalizeAction();
		if (_mainCharacter->main_state()!="4")
		{
			if (_mainCharacter->on_state_end() == true)
				_mainCharacter->set_on_state_end(false);
			_mainCharacter->set_main_state("1");
			if (_mainCharacter->main_state() == "1")
			{
				if (_mainCharacter->on_state_end() == false)
					_mainCharacter->set_prev_main_state("1");
			}
		}
		
		if (_mainCharacter->isClimbing() == false)
			_mainCharacter->set_vx(CHARACTER_VX);
		else
			_mainCharacter->set_vx(0);
		return;
	}
	if (Key_Hold(DIK_Z))
	{
		return;
	}

	//to edit later
	if (_mainCharacter->main_state() != "4"
		|| (_mainCharacter->main_state() == "4" && _mainCharacter->isClimbing() == false))
	{
		_mainCharacter->set_main_state("0");
	}
	if (_mainCharacter->on_state_end()==false && _mainCharacter->prev_main_state()=="1" && _mainCharacter->hand_state()=="0" && _mainCharacter->sub_state()=="0" && _mainCharacter->vy()==0 && _mainCharacter->isClimbing()== false && _mainCharacter->hand_state()=="0" && _mainCharacter->isSwinging()== false)
	{
		_mainCharacter->set_on_state_end(true);
		if (_mainCharacter->degree_state()=="0")
		{
			_mainCharacter->set_state("0001");
			_mainCharacter->set_degree_state("1");
		}
		_mainCharacter->set_prev_main_state("0");
	}
	if (_mainCharacter->on_state_end()==true && _mainCharacter->state_manager()->life_span() <=0 )
	{
		_mainCharacter->set_on_state_end(false);
		_mainCharacter->set_degree_state("0");
	}

	if (_mainCharacter->main_state() == "4" && _mainCharacter->isClimbing() == true)
		_mainCharacter->StopY();
	if (_mainCharacter->main_state() == "0" && _mainCharacter->sub_state() == "5"  && _mainCharacter->isSwinging() == true)
		_mainCharacter->StopY();

	_mainCharacter->StopX();

	return;
}

void Scene2::DisposablePhysicUpdate(float t)
{
	_mainCharacter->set_is_absorbed(false);
	for (auto i = _enemyBulletStarList->begin(); i != _enemyBulletStarList->end();)
	{
		temp_bullet_scene2 = *i;
		if (find(_onScreenList->begin(), _onScreenList->end(), temp_bullet_scene2) == _onScreenList->end() || temp_bullet_scene2->state_manager()->life_span() <= 0)
		{
			temp_star = *i;
			delete temp_star;
			i = _enemyBulletStarList->erase(i);
			_gameObjectList->remove(temp_bullet_scene2);
			_onScreenList->remove(temp_bullet_scene2);
		}
		else
		{
			bulletCollideScene2 = SimpleIntersect(&temp_bullet_scene2->bounding_box(), &_mainCharacter->bounding_box());
			if (temp_bullet_scene2->x() > _mainCharacter->x())
				temp_bullet_scene2->set_vx(-10);
			else temp_bullet_scene2->set_vx(10);
			if (temp_bullet_scene2->y() > _mainCharacter->y())
				temp_bullet_scene2->set_vy(-5);
			else temp_bullet_scene2->set_vy(5);
			//to remove disposable thing out of screen when they are out of sight
			temp_bullet_scene2->setPosition(temp_bullet_scene2->x() + temp_bullet_scene2->vx()* t, temp_bullet_scene2->y() + temp_bullet_scene2->vy()*t);
			if (bulletCollideScene2 == true)
			{
				if (_mainCharacter->is_immune() == 0.0f)
				{
				_mainCharacter->set_vx(_mainCharacter->vx() - temp_bullet_scene2->vx()/5);
				temp_bullet_scene2->set_state("001");
				temp_bullet_scene2->setIsRepeating(false);
				_mainCharacter->set_is_absorbed(true);
				}		
			}
			i++;
		}
	}
	for (auto i = _enemyBulletFireList->begin(); i != _enemyBulletFireList->end();)
	{
		temp_bullet_scene2 = *i;
		if (find(_onScreenList->begin(), _onScreenList->end(), temp_bullet_scene2) == _onScreenList->end())
		{
			delete *i;
			i = _enemyBulletFireList->erase(i);
			_gameObjectList->remove(temp_bullet_scene2);
			_onScreenList->remove(temp_bullet_scene2);
		}
		else
		{
			bulletCollideScene2 = &CheckCollision(temp_bullet_scene2, _mainCharacter);
			//to remove disposable thing out of screen when they are out of sight
			temp_bullet_scene2->setPosition(temp_bullet_scene2->x() + temp_bullet_scene2->vx()* t, temp_bullet_scene2->y() + temp_bullet_scene2->vy()*t);
			if (bulletCollideScene2 == true)
			{
				if (_mainCharacter->is_immune() == 0.0f)
				{
					_mainCharacter->set_health(_mainCharacter->health() - 1);
				}
			}
			i++;
		}
	}
}

void Scene2::JafarAI(GameObjectMove* jafar)
{
	if (_mainCharacter->x() < jafar->x())
		jafar->set_curFace(GameObject::LEFT);
	else jafar->set_curFace(GameObject::RIGHT);
	if (jafar->CheckFlip())
	{
		jafar->set_vx(-jafar->vx());
		jafar->Flip();
	}
	if (jafar->health()==4)
	{
		jafar->set_main_state("1");
	}
	if (jafar->main_state() =="1")
	{
		jafar->set_state("101");
		jafar->set_hand_state("1");
		if (_enemyBulletStarList->size() == 0)
			_Jafar->set_is_throwing(false);
		jafar->setIsRepeating(false);
		if (jafar->is_throwing() == false && jafar->state_manager()->life_span()==3)
		{
			if (drawOneOnAnime==false)
			{
				GameObject* temp_fire = new GameObject();
				FireBulletPrefab::Instantiate(temp_fire, jafar->x(), jafar->y(), jafar->curface());
				_enemyBulletFireList->push_back(temp_fire);
				_gameObjectList->push_back(temp_fire);
				_onScreenList->push_back(temp_fire);
				drawOneOnAnime = true;
			}
			
		}
		if (_Jafar->state_manager()->life_span() <= 0 && _Jafar->is_throwing() == false)
		{
			drawOneOnAnime = false;
			jafar->set_state("100");
			jafar->set_state("101");
		}
		if (_enemyBulletFireList->size() == 1)
			_Jafar->set_is_throwing(true);

	}
	if (jafar->main_state() == "0")
	{
		jafar->set_state("001");
		jafar->set_hand_state("1");
		if (_enemyBulletStarList->size() == 0)
			_Jafar->set_is_throwing(false);
		jafar->setIsRepeating(false);

		if (jafar->state_manager()->life_span()<=5 && jafar->state_manager()->life_span() >=3 && jafar->hand_state()=="1" && jafar->is_throwing()== false)
		{
			temp_star = new GameObject();
			StarBulletPrefab::Instantiate(temp_star, _Jafar->x(), _Jafar->y(), _Jafar->curface());
			_enemyBulletStarList->push_back(temp_star);
			_gameObjectList->push_back(temp_star);
			_onScreenList->push_back(temp_star);
			//_disposableList->push_back(temp_star);
		}
		


		if (_Jafar->state_manager()->life_span() <= 0 && _Jafar->is_throwing() == false)
		{
			jafar->set_state("000");
			jafar->set_state("001");
		}

		if (_enemyBulletStarList->size() >= 20)
			_Jafar->set_is_throwing(true);
	}

}

void Scene2::PhysicsUpdate(float t)
{
	JafarAI(_Jafar);
	_Jafar->PhysicUpdate(t);
	DisposablePhysicUpdate(t);
	if (_mainCharacter->on_state_end() == false)
	{
		_mainCharacter->setState(_mainCharacter->main_state() + _mainCharacter->sub_state() + _mainCharacter->hand_state());
	}
	CollisionDetect();
	_mainCharacter->PhysicUpdate(t);
}

void Scene2::GraphicUpdate(float t)
{
	_mainCharacter->GraphicUpdate(t);
	MyCamera::GetInstance()->Update(t);

	//Render Everything
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);

	viewRect = MyCamera::GetInstance()->View();
	d3ddev->BeginScene();
	//start sprite handler 	
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);
	sprite_handler->SetTransform(&old_matrix);
	
	sprite_handler->Draw(mapETC, &viewRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//sprite_handler->Draw(mapETC, &viewRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	_mainCharacter->setTranslation(D3DXVECTOR2(_mainCharacter->x() - MyCamera::GetInstance()->View().left, _mainCharacter->y() - MyCamera::GetInstance()->View().top));
	_mainCharacter->DrawBullet();
	_mainCharacter->RenderBounding(D3DCOLOR_ARGB(200, 255, 67, 78));
	_mainCharacter->Render(false, true, true);
	for (auto i = _onScreenList->begin(); i != _onScreenList->end(); i++)
	{
		temp_object_scene2 = *i;
		temp_object_scene2->setAnchor(AnchorPoint::BOTTOM_MID);
		temp_object_scene2->setTranslation(D3DXVECTOR2(temp_object_scene2->x() - viewRect.left, temp_object_scene2->y() - viewRect.top));
		if (temp_object_scene2->sprite()->image())
		{
			temp_object_scene2->Render(false, true, true);
			temp_object_scene2->GraphicUpdate(t);
		}
		temp_object_scene2->RenderBounding(D3DCOLOR_ARGB(200, 255, 67, 78));
	}

	//mainCharacter->RenderBounding(D3DCOLOR_ARGB(150, 0, 250, 0));
	sprite_handler->End();
	//stop rendering 
	d3ddev->EndScene();

}

list<GameObject*>* Scene2::OnScreenDetect()
{
		Quadtree* quadtree = Quadtree::CreateQuadtree(0, 0, mapinfo->Width, mapinfo->Height);
		list<GameObject*>* return_object_list = new list<GameObject*>();
		quadtree->Retrieve(return_object_list, MyCamera::GetInstance());
		return return_object_list;
}


void Scene2::Game_Run(HWND hwnd, int)
{
	GameTime::GetInstance()->StartCounter();
	InputUpdate();

	//make sure the Direct3D device is valid
	if (d3ddev == NULL)
		return;
	DWORD now = GetTickCount();
	//this keeps the game running at a steady frame rate
	float t = now - startScene2;
	if (t >= 1000 / FPS)
	{

		//reset timing
		startScene2 = now;
		if (t < FIXED_TIME)
			Sleep(FIXED_TIME - t);
		_onScreenList = OnScreenDetect();
		PhysicsUpdate(FIXED_TIME);
		GraphicUpdate(FIXED_TIME);
		_onScreenList->clear();
	}
	//display the back buffer on the screen
	d3ddev->Present(NULL, NULL, NULL, NULL);
	//check for escape key (to exit program)	
	if (KEY_PRESSED(VK_ESCAPE))
		PostMessage(hwnd, WM_DESTROY, 0, 0);

}

void Scene2::Game_End(HWND)
{
}

void Scene2::LoadListObjectXml(char* xmlpath)
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
			if (name == "Ground" ||  name == "Wall" || name =="Pedestal")
			{
				anchorTransformY = atoi(object.attribute("height").value());
			}
			anchorTransformX = atoi(object.attribute("width").value()) / 2;
			OutputDebugString(to_string(idName).c_str());
			OutputDebugString("\n");

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
			
			default:
				anObject = new GameObject();
				break;
			}
			anObject->setAnchor(AnchorPoint::BOTTOM_MID);
			 
			anObject->set_bounding_box(CalculateBoundingBox(anObject->x(), anObject->y(), anObject->width(), anObject->height(), anObject->anchor()));
			(CalculateBoundingBox(anObject->x(), anObject->y(), anObject->width(), anObject->height(), anObject->anchor()));
			 
			_gameObjectList->push_back(anObject);
		}
	}

}

Scene2::Scene2()
{
}


Scene2::~Scene2()
{
}
