#include "includeAll.h"
#include "Map.h"

Map::Map(float width, float height, const VideoMode& vm)
{
	this->width = width;
	this->height = height;
	this->vm = vm;
	this->changeMap = false;
}

Map::~Map()
{

}

const bool& Map::getChangeMap() const
{
	return this->changeMap;
}

void Map::endState()
{
	this->changeMap = true;
}
