#include "GameObjectMove.h"
#include "trace.h"


GameObjectMove::GameObjectMove()
{
	GameObject::GameObject();
	_isThrowing = false;
	_isImmune = 0.0f;
	_health = 0;
}

void GameObjectMove::GraphicUpdate(float t)
{
	GameObject::GraphicUpdate(t);



}

void GameObjectMove::PhysicUpdate(float t)
{
	if (_isImmune != 0.0f)
		_isImmune--;
	if (_handState == "2" && _stateManager->life_span() == 3)
	{
		CalSword();
		//trace(L"%d", _stateManager->life_span());
	}
	if (_handState == "2" && _stateManager->life_span() == 1)
	{
		_handState = "0";
		DelSword();		
	}
}

void GameObjectMove::CalSword()
{

	if (main_state() == "2")
	{
		_sword = &getBoundingBox(main_state() + sub_state() + "2");
		return;
	}
	RECT temp_rect1 = getBoundingBox(main_state() + sub_state() + "2");
	RECT temp_rect2 = getBoundingBox(main_state() + sub_state() + "0");
	_sword->top = _boundingBox.top;
	_sword->bottom = _boundingBox.bottom;
	if (curface() == Face::RIGHT)
	{
		_sword->left = temp_rect2.right;
		_sword->right = temp_rect1.right;
		return;
	}
	else
	{
		_sword->left = temp_rect1.left;
		_sword->right = temp_rect2.left;
		return;
	}

}

void GameObjectMove::DelSword()
{
	_sword->bottom = 0;
	_sword->top = 0;
	_sword->right = 0;
	_sword->left = 0;
}

GameObjectMove::~GameObjectMove()
{
	
}

int GameObjectMove::health()
{
	return _health;
}

void GameObjectMove::set_health(int newHealth)
{
	_health = newHealth;
}
