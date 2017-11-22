#include "CamelPrefab.h"

void CamelPrefab::Instantiate(GameObject* gameObject, float x, float y, int width, int height)
{
	gameObject->set_name("Camel");
	gameObject->setPosition(x, y);
	gameObject->setSprite(new Sprite("Res\\Camel.png", width,height));
	gameObject->set_state_manager(new StateManager("Res\\CamelXML.xml"));
	gameObject->state_manager()->AddToDictState("0", "CamelIdle"); 
	gameObject->state_manager()->AddToDictState("1", "CamelBeaten");
	gameObject->state_manager()->setState("1");
	gameObject->setAnimaDelay(1);
	gameObject->setIsRepeating(false);
}

void CamelPrefab::BeBeaten(GameObject * gameObject)
{ 
	gameObject->Reset(); 
}
CamelPrefab::CamelPrefab()
{
}


CamelPrefab::~CamelPrefab()
{
}
