#include "EnemyThinPrefab.h"

void EnemyThinPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("EnemyThin");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Enemy1.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyThinXML.xml"));
	gameObject->state_manager()->AddToDictState("0", "EnemyThinIdle");
	gameObject->state_manager()->AddToDictState("1", "EnemyThinRun");
	gameObject->state_manager()->AddToDictState("2", "EnemyThinSlash");
	gameObject->state_manager()->AddToDictState("3", "EnemyThinBeaten");
	gameObject->state_manager()->setState("0");
} 

EnemyThinPrefab::EnemyThinPrefab()
{
}


EnemyThinPrefab::~EnemyThinPrefab()
{
}
