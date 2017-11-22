#pragma once
#include "GameObjectMove.h";

class EnemyJugPrefab
{
public:
	static void Instantiate(GameObjectMove*, float, float, int, int);
	EnemyJugPrefab();
	~EnemyJugPrefab();
};

