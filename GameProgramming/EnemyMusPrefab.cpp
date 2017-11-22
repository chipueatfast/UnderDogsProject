#include "EnemyMusPrefab.h"

void EnemyMusPrefab::Instantiate(GameObjectMove* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("EnemyMus");
	gameObject->set_health(3);
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Enemy1.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyMusXML.xml"));
	gameObject->state_manager()->AddToDictState("000", "EnemyMusTaunt");
	gameObject->state_manager()->AddToDictState("001", "EnemyMusRun");
	gameObject->state_manager()->AddToDictState("002", "EnemyMusRun"); 
	gameObject->state_manager()->AddToDictState("005", "EnemyMusSlash");
	gameObject->state_manager()->AddToDictState("004", "EnemyMusSlash"); 
	gameObject->state_manager()->AddToDictState("003", "EnemyMusBeaten");
	gameObject->set_main_state("0");
	gameObject->set_sub_state("0");
	gameObject->set_hand_state("0");
	gameObject->state_manager()->setState("000");
}

EnemyMusPrefab::EnemyMusPrefab()
{
}


EnemyMusPrefab::~EnemyMusPrefab()
{
}
