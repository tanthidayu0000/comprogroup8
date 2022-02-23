#include "includeAll.h"
#include "Map.h"

Map::Map(float width, float height, const VideoMode& vm)
{
	this->width = width;
	this->height = height;
	this->vm = vm;
	this->changeMap = false;
	this->restart = false;
	this->damage = 0;
}

Map::~Map()
{

}

const bool& Map::getChangeMap() const
{
	return this->changeMap;
}

int Map::getdamage()
{
	return this->damage;
}

const bool Map::updaterestart()
{
	return this->restart;
}

void Map::endState()
{
	this->changeMap = true;
}
