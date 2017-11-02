#include "StateRaw.h"



StateRaw::StateRaw()
{
}


StateRaw::~StateRaw()
{
}

StateRaw::StateRaw(char* path, const std::string stateName)
{
	_name = stateName;
	xml_document fileXml;
	xml_parse_result result = fileXml.load(path);
	xml_node root = fileXml.child("Animations");

	for (xml_node nodeAnimation = root.first_child(); nodeAnimation; nodeAnimation = nodeAnimation.next_sibling())
	{

		if (nodeAnimation.attribute("name").value() == stateName)
		{
			_countPositions = 0;
			RECT *rect;

			for (xml_node nodeRec = nodeAnimation.first_child(); nodeRec; nodeRec = nodeRec.next_sibling())
			{
				_countPositions++;
			}

			_positions = new RECT[4];
			int i = 0;
			for (xml_node nodeRec = nodeAnimation.first_child(); nodeRec; nodeRec = nodeRec.next_sibling(), ++i)
			{
				_positions[i].top = LONG(nodeRec.attribute("y").value());
				_positions[i].left = LONG(nodeRec.attribute("x").value());
				_positions[i].bottom = LONG(nodeRec.attribute("h").value()) + _positions[i].top;
				_positions[i].right = LONG(nodeRec.attribute("w").value()) + _positions[i].left;
			}
		}
	}
}

RECT* StateRaw::getPositions() const
{
	return _positions;
}

int StateRaw::getCountPos() const
{
	return _countPositions;
}

std::string StateRaw::getName() const
{
	return _name;
}
