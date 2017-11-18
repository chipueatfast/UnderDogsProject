#include "EnemyMusPrefab.h"

void EnemyMusPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("EnemyMus");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Enemy1.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyMusXML.xml"));
	gameObject->state_manager()->AddToDictState("0", "EnemyMusIdle");
	gameObject->state_manager()->AddToDictState("1", "EnemyMusRun");
	gameObject->state_manager()->AddToDictState("2", "EnemyMusRun"); 
	gameObject->state_manager()->AddToDictState("3", "EnemyMusSlash");
	gameObject->state_manager()->AddToDictState("4", "EnemyMusSlash"); 
	gameObject->state_manager()->AddToDictState("5", "EnemyMusBeaten");
	gameObject->state_manager()->setState("0");
}

EnemyMusPrefab::EnemyMusPrefab()
{
}


EnemyMusPrefab::~EnemyMusPrefab()
{
}
