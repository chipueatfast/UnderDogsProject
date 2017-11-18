#include "EnemyJugPrefab.h"

void EnemyJugPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("EnemyJug");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Enemy2.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyJugXML.xml"));
	gameObject->state_manager()->AddToDictState("0", "EnemyJugIdle");  
	gameObject->state_manager()->AddToDictState("2", "EnemyJugSlash1");
	gameObject->state_manager()->AddToDictState("3", "EnemyJugSlash2"); 
	gameObject->state_manager()->setState("0");
}

EnemyJugPrefab::EnemyJugPrefab()
{
}


EnemyJugPrefab::~EnemyJugPrefab()
{
}
