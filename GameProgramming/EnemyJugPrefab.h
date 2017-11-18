#pragma once
#include "GameObjectMove.h";

class EnemyJugPrefab
{
public:
	static void Instantiate(GameObject*, float, float, int, int);

	EnemyJugPrefab();
	~EnemyJugPrefab();
};

