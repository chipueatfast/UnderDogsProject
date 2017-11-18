#pragma once
#include "GameObject.h";
class GameObjectMove :public GameObject
{
private:
	int _health;
public:
	GameObjectMove();
	~GameObjectMove();
	int health() ;
	void set_health(int newHealth);
};

