#pragma once
#include "GameObjectMove.h";

class EnemyFatPrefab
{
public:
	static void Instantiate(GameObjectMove*,float ,float, int, int);
	EnemyFatPrefab();
	~EnemyFatPrefab();
};

