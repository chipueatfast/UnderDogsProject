#include "EnemyFatPrefab.h"
 
void EnemyFatPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{ 
	gameObject->set_name("EnemyFat");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Enemy1.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyFatXML.xml")); 
	gameObject->state_manager()->AddToDictState("0", "EnemyFatIdle");
	gameObject->state_manager()->AddToDictState("1", "EnemyFatRun");
	gameObject->state_manager()->AddToDictState("2", "EnemyFatSlash");
	gameObject->state_manager()->AddToDictState("3", "EnemyFatBeaten");
	gameObject->state_manager()->setState("0");  
}

EnemyFatPrefab::EnemyFatPrefab()
{
}


EnemyFatPrefab::~EnemyFatPrefab()
{
}
