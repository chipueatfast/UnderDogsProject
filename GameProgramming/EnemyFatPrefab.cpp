#include "EnemyFatPrefab.h"
 
void EnemyFatPrefab::Instantiate(GameObjectMove* gameObject, float x, float y, int width, int height)
{ 
	gameObject->set_name("EnemyFat");
	gameObject->set_health(3);
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Enemy1.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyFatXML.xml")); 
	gameObject->state_manager()->AddToDictState("000", "EnemyFatIdle");
	gameObject->state_manager()->AddToDictState("001", "EnemyFatRun");
	gameObject->state_manager()->AddToDictState("002", "EnemyFatSlash");
	gameObject->state_manager()->AddToDictState("003", "EnemyFatBeaten");
	gameObject->set_main_state("0");
	gameObject->set_hand_state("0");
	gameObject->set_sub_state("0");
	gameObject->state_manager()->setState("000");  
}

EnemyFatPrefab::EnemyFatPrefab()
{
}


EnemyFatPrefab::~EnemyFatPrefab()
{
}
