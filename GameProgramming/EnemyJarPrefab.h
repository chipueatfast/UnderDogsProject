#pragma once
#include "GameObjectMove.h";

class EnemyJarPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);

	EnemyJarPrefab();
	~EnemyJarPrefab();
};

