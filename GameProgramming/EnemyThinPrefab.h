#pragma once
#include "GameObjectMove.h";

class EnemyThinPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);

	EnemyThinPrefab();
	~EnemyThinPrefab();
};

