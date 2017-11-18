#pragma once
#include "GameObjectMove.h";

class EnemyMusPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);

	EnemyMusPrefab();
	~EnemyMusPrefab();
};

