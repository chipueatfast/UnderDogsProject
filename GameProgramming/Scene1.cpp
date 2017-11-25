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
#include "BulletPrefab.h"


#define GRAVITY 10
#define JUMP_FORCE -55



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
	_onScreenList = new list<GameObject*>();
	_healthHavingList = new list<GameObjectMove*>();
	_disposableList = new list<GameObject*>();
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
	mapIdName["ParabolKnife"] = 16;
	mapIdName["StraightKnife"] = 17;
#pragma region Sound
	_soundTheme = LoadSound("Res/Audio/LifeCollect.wave");
	_soundJump = LoadSound("Cuica-1.wave");
	_soundSlash = LoadSound("Res/Audio/IdleDownSplash.wave");
	
	_soundCollectApple = LoadSound("Res/Audio/AppleCollect.wave");
	_soundCamel = LoadSound("Res/Audio/Camel.wave");
	_soundSpringBoard = LoadSound("Res/Audio/SpringBroad.wave");
	_soundAppleCollision = LoadSound("Res/Audio/AppleThrowCollision.wave");
#pragma endregion
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

	 
	_UI = new UIScene1();
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
	case DIK_U:
		mainCharacter->set_health(mainCharacter->health() + 1);
		break;
	case DIK_I:
		mainCharacter->set_health(mainCharacter->health() - 1);
		break;
	case DIK_SPACE:
		PlaySound(_soundJump);
		break;
	case DIK_X:
		mainCharacter->set_hand_state("2");
		_soundSlash->Play();
		break;
	case DIK_C:
		mainCharacter->set_hand_state("1");
		mainCharacter->FireApple();
		
		break;
	case DIK_Z:
		if (mainCharacter->sub_state() != "1" && mainCharacter->sub_state() != "2" && mainCharacter->sub_state() != "5")
		{
			mainCharacter->set_sub_state("2");
			mainCharacter->setIsClimbing(false);
			mainCharacter->set_vy(JUMP_FORCE);
		}
		else
		{
			if (mainCharacter->sub_state() == "5")
				mainCharacter->setIsSwinging(false);
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
		if (mainCharacter->main_state() == "4")
		{
			mainCharacter->set_vy(-CHARACTER_VX);
			return;
		}

		mainCharacter->set_main_state("2");
		mainCharacter->StopX();
		return;

	};

	if (Key_Hold(DIK_DOWN))
	{
		if (mainCharacter->main_state() == "4")
		{
			mainCharacter->set_vy(CHARACTER_VX);
			return;
		}
		mainCharacter->StopX();
		mainCharacter->set_main_state("3");
		return;
	}

	if (Key_Hold(DIK_LEFT))
	{
		if (mainCharacter->main_state() != "4")
		{
			mainCharacter->set_main_state("1");
		}

		if (mainCharacter->isClimbing() == false)
			mainCharacter->set_vx(-CHARACTER_VX);
		else
			mainCharacter->set_vx(0);
		return;
	}
	if (Key_Hold(DIK_RIGHT))
	{
		if (mainCharacter->main_state() != "4")
		{
			mainCharacter->set_main_state("1");
		}
		if (mainCharacter->isClimbing() == false)
			mainCharacter->set_vx(CHARACTER_VX);
		else
			mainCharacter->set_vx(0);
		return;
	}
	if (Key_Hold(DIK_Z))
	{
		return;
	}
//to edit later
	if (mainCharacter->main_state() != "4"
		|| (mainCharacter->main_state() == "4" && mainCharacter->isClimbing() == false))
	{
		mainCharacter->set_main_state("0");

	}
	if (mainCharacter->main_state() == "4" && mainCharacter->isClimbing() == true)
		mainCharacter->StopY();
	if (mainCharacter->main_state() == "0" && mainCharacter->sub_state() == "5"  && mainCharacter->isSwinging() == true)
		mainCharacter->StopY();

	mainCharacter->StopX();

	return;


}

void Scene1::DisposablePhysicUpdate(float t)
{
	for (auto i = _disposableList->begin(); i!= _disposableList->end(); i++)
	{		
		GameObject* bullet= *i;
		switch (mapIdName[bullet->get_name()])
		{
		case 17:
			bullet->set_vy(0);
			break;
		}
		bullet->setPosition(bullet->x() + bullet->vx()*t, bullet->y() + bullet->vy()*t);
		if (find(_onScreenList->begin(), _onScreenList->end(), bullet) == _onScreenList->end())
		{
			//bullet->setVisible(false);
			_gameObjectList->remove(bullet);
			/*_disposableList->erase(i);*/
			//listToDelete->push_back(bullet);
		}		
	}


}

void Scene1::CollisionDetect()
{
	Quadtree* quadtree = Quadtree::CreateQuadtree(MyCamera::GetInstance()->bounding_box().left, MyCamera::GetInstance()->bounding_box().top, MyCamera::GetInstance()->bounding_box().right, MyCamera::GetInstance()->bounding_box().bottom);

	std::list<GameObject*>* return_object_list = new std::list<GameObject*>();
	quadtree->Retrieve(return_object_list, MyCamera::GetInstance());
	for (auto x = return_object_list->begin(); x != return_object_list->end(); x++)
		//for(auto x = _gameObjectList->begin(); x != _gameObjectList->end();x++)
	{
		GameObject *temp_obj = *x;
		if (temp_obj->Visbile() == true)
		{
			mainCharacter->set_bounding_box(CalculateBoundingBox(mainCharacter->x(), mainCharacter->y(), mainCharacter->width(), mainCharacter->height(), mainCharacter->anchor()));
			temp_obj->set_bounding_box(CalculateBoundingBox(temp_obj->x(), temp_obj->y(), temp_obj->width(), temp_obj->height(), temp_obj->anchor()));


			CollisionResult collisionResult = CheckCollision(mainCharacter, temp_obj);


			if (collisionResult._collisionIndex < 1 && collisionResult._collisionIndex >= 0)
			{
				//MainCharacter collision with others z
				int collisionNameID = mapIdName[temp_obj->get_name()];
				switch (collisionNameID)
				{
				case 0://Apple
					temp_obj->setVisible(false);
					mainCharacter->setAppleCount(mainCharacter->appleCount() + 1);
					//sound
					_soundCollectApple->Play();
					break;
				case 1://Ground

					if (collisionResult._collisionSide == UP)
					{
						mainCharacter->set_vy(-collisionResult._collisionIndex*mainCharacter->vy());
					}
					if (collisionResult._collisionSide == DOWN)
					{
						mainCharacter->set_vy((collisionResult._collisionIndex*mainCharacter->vy()));
					}
					if (collisionResult._collisionSide == LEFT || collisionResult._collisionSide == RIGHT)
					{
						mainCharacter->set_vx(0);
					}
					break;
				case 2: //Wall

					mainCharacter->set_vx(0);
					mainCharacter->set_sub_state("3");
					break;

				case 3://Rope
					if (mainCharacter->sub_state() == "1" || mainCharacter->isClimbing() == true)
					{
						mainCharacter->setIsClimbing(true);
						if (mainCharacter->bounding_box().top >= temp_obj->bounding_box().top)
						{
							mainCharacter->setPosition(temp_obj->x(), mainCharacter->y());
							//mainCharacter->set_sub_state("1");
						}
						else
						{
							if (mainCharacter->vy() < 0)
								mainCharacter->set_vy(0);
							mainCharacter->set_sub_state("1");
						}
						mainCharacter->set_vx(0);
						mainCharacter->set_main_state("4");
						//MyCamera::GetInstance()->setPosition(temp_obj->x(), MyCamera::GetInstance()->y());
					}




					break;
				case 4://HorizontalBar
				{
					if (mainCharacter->sub_state() == "1"
						|| mainCharacter->sub_state() == "2"
						|| mainCharacter->isSwinging() == true)
					{
						mainCharacter->StopY();
						string str;
						str = mainCharacter->main_state() + "5" + mainCharacter->hand_state();


						mainCharacter->setIsSwinging(true);
						int height;

						OutputDebugString("\n");
						OutputDebugString(str.c_str());
						height = mainCharacter->state_manager()->getStateByCode(str).getListRect().at(0).bottom - mainCharacter->state_manager()->getStateByCode(str).getListRect().at(0).top;
						OutputDebugString(("  : " + to_string(height)).c_str());
						if (mainCharacter->bounding_box().left >= temp_obj->bounding_box().left
							&& mainCharacter->bounding_box().right <= temp_obj->bounding_box().right)
						{
							mainCharacter->setPosition(mainCharacter->x(), temp_obj->CalPositon(TOP_LEFT).y + height);
						}
						if (mainCharacter->bounding_box().left < temp_obj->bounding_box().left && mainCharacter->vx() < 0)
						{
							mainCharacter->StopX();
							mainCharacter->setPosition(temp_obj->CalPositon(TOP_LEFT).x + mainCharacter->width()/2, temp_obj->CalPositon(TOP_LEFT).y + height);
						}
						if (mainCharacter->bounding_box().right > temp_obj->bounding_box().right && mainCharacter->vx() > 0)
						{

							mainCharacter->StopX();
							mainCharacter->setPosition(temp_obj->CalPositon(TOP_RIGHT).x - mainCharacter->width() / 2, temp_obj->CalPositon(TOP_LEFT).y + height);
						}
						mainCharacter->set_sub_state("5");
						//mainCharacter->set_sub_state("1");
					}
					MyCamera::GetInstance()->setPosition(temp_obj->x(), MyCamera::GetInstance()->y());

					//mainCharacter->set_main_state("0");
				}
				break;

				case 5://FloatGround
					break;
				case 6://SpringBoard
					mainCharacter->set_sub_state("6");
					mainCharacter->set_vy(JUMP_FORCE*0.8f);

					_soundSpringBoard->Play();
					break;
				case 7://Camel
					if (mainCharacter->sub_state() == "1" && collisionResult._collisionSide == DOWN)
					{
						mainCharacter->set_sub_state("2");
						//mainCharacter->setPosition(mainCharacter->x() + collisionResult._collisionIndex*mainCharacter->vx()*FIXED_TIME, mainCharacter->y() + collisionResult._collisionIndex*mainCharacter->vy()*FIXED_TIME);
						mainCharacter->set_vy(JUMP_FORCE*0.5);
						//event 
						CamelPrefab::BeBeaten(temp_obj);
						//sound
						_soundCamel->Play();
					}
					break;
				case 11:case 12:
				case 13:case 14: case 15:
					mainCharacter->BeBeaten();
					break;

				default: {}
				}
			}
		}
		for (list<GameObject*>::iterator obj = _onScreenList->begin(); obj != _onScreenList->end(); obj++)
		{
			for(auto ab = mainCharacter->bullet_list()->begin(); ab!= mainCharacter->bullet_list()->end(); ab++ )
			{ 
				AppleBullet* x = *ab;
				if (x->Visbile() == true)
				{
					CollisionResult collisionIndex = CheckCollision(*ab, *obj);
					if (collisionIndex._collisionIndex<1.0f && collisionIndex._collisionIndex > 0.0f)
					{

						x->set_vx(collisionIndex._collisionIndex * x->vx());
						x->set_vy(collisionIndex._collisionIndex * x->vy());
						break;
					}
					if (collisionIndex._collisionIndex == 0.0f)
					{
						x->set_is_popping(true);
						x->state_manager()->setState("001");
						x->set_vx(0);
						x->set_vy(0);
						_soundAppleCollision->Play();
						if (temp_obj->get_name() == "EnemyFat")
						{

							auto temp_obj2 = new GameObjectMove();
							temp_obj2 = (GameObjectMove*)*obj;
							if (temp_obj2->is_immune() == 0.0f)
							{
								temp_obj2->set_health(temp_obj2->health() - 1);
								temp_obj2->set_is_immune(30);
								if (temp_obj2->health() == 0)
									temp_obj2->set_state("003");
							}


						}
					}
				}
			}
			//Process sword 
			GameObject* temp_obj = *obj;
			if (SimpleIntersect(mainCharacter->sword(), &temp_obj->bounding_box()))
			{
				if (temp_obj->get_name() == "EnemyFat" || temp_obj->get_name()=="EnemyMus")
				{
				
					auto temp_obj2 = new GameObjectMove();
					temp_obj2 = (GameObjectMove*)*obj;
					if (temp_obj2->is_immune() == 0.0f)
					{
						temp_obj2->set_health(temp_obj2->health() - 1);
						temp_obj2->set_is_immune(30);
						if (temp_obj2->health() == 0)
							temp_obj2->set_state("003");
					}

					
				}
			}
		}
	

	}



}
void Scene1::PhysicsUpdate(float t)
{

	//handle physic of all enemies
	for (auto i=_healthHavingList->begin(); i!= _healthHavingList->end(); i++)
	{
	
		if (std::find(_onScreenList->begin(), _onScreenList->end(), (GameObject*)*i) != _onScreenList->end())
		{
			
			GameObjectMove* game_obj = *i;
			if (std::find(_onScreenList->begin(), _onScreenList->end(), game_obj->weapon_obj()) == _onScreenList->end())
				game_obj->set_is_throwing(false);
			if (mainCharacter->x() < game_obj->x())
				game_obj->set_curFace(GameObject::LEFT);
			else game_obj->set_curFace(GameObject::RIGHT);
			if (game_obj->CheckFlip())
				game_obj->Flip();
			game_obj->PhysicUpdate(t);
			switch (mapIdName[game_obj->get_name()])
			{
			case 13:
				if (abs(mainCharacter->x() - game_obj->x())>80 && game_obj->is_throwing() == false)
				{
					game_obj->set_state("002");
					GameObject* bullet = new GameObject();
					D3DXVECTOR3 temp_pos = (game_obj->curface() == GameObject::RIGHT) ? game_obj->CalPositon(TOP_RIGHT) : game_obj->CalPositon(TOP_LEFT);

					BulletPrefab::Instantiate(bullet, "Knife", temp_pos.x, temp_pos.y, game_obj->curface());

					bullet->set_name("StraightKnife");
					game_obj->set_weapon_obj(bullet);
					_disposableList->push_back(bullet);
					_gameObjectList->push_back(bullet);
					_onScreenList->push_back(bullet);
					game_obj->set_is_throwing(true);
				}
			/*case 14:
				if (abs(mainCharacter->x()-game_obj->x())>250)
				{
					GameObject* bullet = new GameObject();
					BulletPrefab::Instantiate(bullet, "Knife", game_obj->x(), game_obj->y(), game_obj->curface());
					
					bullet->set_name("ParabolKnife");
					_disposableList->push_back(bullet);
				}*/
			}
		}
	}

	
	DisposablePhysicUpdate(t);

	if (mainCharacter->vy() == 0)
	{
		if (mainCharacter->isSwinging() == false)
			mainCharacter->set_sub_state("0");
	}
	if (mainCharacter->vy() > 0)
	{
		mainCharacter->set_sub_state("1");
	}

	if (mainCharacter->isClimbing() == false && mainCharacter->isSwinging() == false)
		mainCharacter->set_vy(mainCharacter->vy() + GRAVITY);
	//else
	//	if( mainCharacter->isSwinging() == false)
	//		mainCharacter->set_vy(mainCharacter->vy() + GRAVITY);
	else
		if (mainCharacter->vy() == 0)
		{
			MyCamera::GetInstance()->set_vy(0);
		}

	CollisionDetect();
	mainCharacter->setState(mainCharacter->main_state() + mainCharacter->sub_state() + mainCharacter->hand_state());
	
	mainCharacter->PhysicUpdate(t);

}

void Scene1::GraphicUpdate(float t)
{

	


	//Render Everything
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->StretchRect(background, NULL, backbuffer, NULL, D3DTEXF_NONE);

	viewRect = MyCamera::GetInstance()->View();
	d3ddev->BeginScene();
	 //erase the entire background 
	
	//start sprite handler 	
	sprite_handler->Begin(D3DXSPRITE_ALPHABLEND);

	sprite_handler->SetTransform(&old_matrix);
	sprite_handler->Draw(mapETC, &viewRect,NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	mainCharacter->setTranslation(D3DXVECTOR2(mainCharacter->x() - MyCamera::GetInstance()->View().left, mainCharacter->y() - MyCamera::GetInstance()->View().top));
	mainCharacter->Render(false, true, true);
	mainCharacter->DrawBullet();
	//for (auto i = _disposableList->begin(); i!= _disposableList->end(); i++)
	//{
	//	GameObject* bullet = *i;
	//	bullet->setAnchor(AnchorPoint::BOTTOM_MID);
	//	bullet->setTranslation(D3DXVECTOR2(bullet->x() - viewRect.left, bullet->y() - viewRect.top));
	//	bullet->Render(false, true, true);
	//	bullet->GraphicUpdate(t);
	//	bullet->RenderBounding(D3DCOLOR_ARGB(200, 255, 0, 0));
	//}

	for (auto i = _onScreenList->begin(); i != _onScreenList->end(); i++)
	{
		GameObject* temp_object = *i;
		temp_object->setAnchor(AnchorPoint::BOTTOM_MID);
		temp_object->setTranslation(D3DXVECTOR2(temp_object->x() - viewRect.left, temp_object->y() - viewRect.top));
		temp_object->Render(false, true, true);
		temp_object->GraphicUpdate(t);
		//temp_object->RenderBounding(D3DCOLOR_ARGB(200, 255, 0, 0));
	}
	

#pragma region Draw map_front
	viewRect.top += mapinfo->Height / 2;
	viewRect.bottom += mapinfo->Height / 2;
	sprite_handler->SetTransform(&old_matrix);
	sprite_handler->Draw(mapETC, &viewRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	
#pragma endregion

	//mainCharacter->RenderBounding(D3DCOLOR_ARGB(150, 0, 250, 0));
	_UI->Render(mainCharacter->health());
	sprite_handler->End();
	//stop rendering 
	d3ddev->EndScene();
	_UI->RenderText(5, mainCharacter->appleCount());
	mainCharacter->GraphicUpdate(t);

	MyCamera::GetInstance()->Update(t);

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
				EnemyMusPrefab::Instantiate((GameObjectMove*)anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				_healthHavingList->push_back((GameObjectMove*)anObject);
				break;
			case 13:
				anObject = new GameObjectMove();
				EnemyFatPrefab::Instantiate((GameObjectMove*)anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				_healthHavingList->push_back((GameObjectMove*)anObject);
				break;
			case 14:
				anObject = new GameObjectMove();
				EnemyJugPrefab::Instantiate((GameObjectMove*)anObject, atoi(object.attribute("x").value()) + anchorTransformX, atoi(object.attribute("y").value()) + anchorTransformY, atoi(object.attribute("width").value()), atoi(object.attribute("height").value()));
				_healthHavingList->push_back((GameObjectMove*)anObject);
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

void Scene1::Game_End(HWND)
{
}


Scene1::~Scene1()
{
}