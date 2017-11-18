#include "GameObjectMove.h"



GameObjectMove::GameObjectMove()
{
	GameObject::GameObject();
	_health = 0;
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
