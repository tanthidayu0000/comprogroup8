#include "includeAll.h"
#include "Door.h"

void Door::initTexture()
{
	if (!this->textureSheet.loadFromFile("Sprites/door.png"))
	{
		cout << "ERROR::DOOR::Cloud not load the door sheet!";
	}
}

void Door::initSprite(float x, float y, const VideoMode& vm)
{
	this->door.setTexture(&this->textureSheet, true);
	this->currentFrame = IntRect(0, 0, 32, 32);

	this->door.setTextureRect(this->currentFrame);
	this->door.setSize(Vector2f(gui::p2pX(2.5f, vm), gui::p2pY(4.45f, vm)));
	this->door.setPosition(x, y);
}

Door::Door(float x, float y, const VideoMode& vm)
{
	this->initTexture();
	this->initSprite(x, y, vm);
}

Door::~Door()
{

}

const Vector2f Door::getGlobalBounds() const
{
	return this->door.getSize();
}

const Vector2f Door::getPos()
{
	return this->door.getPosition();
}

void Door::update()
{

}

void Door::render(RenderTarget* target)
{
	target->draw(this->door);
}
