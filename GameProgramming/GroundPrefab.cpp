#include "GroundPrefab.h"

void GroundPrefab::Instantiate(GameObject* object, int x, int y, int width, int height)
{
	object->set_name("ground");
	object->setPosition(x, y);
	object->set_height(height);
	object->set_width(width);
	object->set_bounding_box(CalculateBoundingBox(x, y, width, height));
	//object->setSprite(nullptr);
	return;
}
