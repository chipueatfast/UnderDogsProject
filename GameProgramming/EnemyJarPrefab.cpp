#include "EnemyJarPrefab.h"

void EnemyJarPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("EnemyJar");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Enemy2.png", width, height));
	gameObject->set_state_manager(new StateManager("Res\\EnemyJarXML.xml"));
	gameObject->state_manager()->AddToDictState("0", "EnemyJarIdle");
	gameObject->state_manager()->AddToDictState("1", "EnemyJarRun");
	gameObject->state_manager()->AddToDictState("2", "EnemyJarSlash");
	gameObject->state_manager()->AddToDictState("3", "EnemyJarBeaten");
	gameObject->state_manager()->setState("0");
}

EnemyJarPrefab::EnemyJarPrefab()
{
}


EnemyJarPrefab::~EnemyJarPrefab()
{
}
