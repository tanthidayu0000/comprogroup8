#include "includeAll.h"
#include "heart.h"

void Heart::initTexture()
{
	if (!this->textureSheet.loadFromFile("Sprites/heart.png"))
	{
		cout << "ERROR::HEART::Cloud not load the heart sheet!";
	}
}

void Heart::initSprite(float x, float y, const VideoMode& vm)
{
	this->heart.setTexture(&this->textureSheet, true);

	this->heart.setSize(Vector2f(gui::p2pX(2.5f, vm), gui::p2pY(4.45f, vm)));
	this->heart.setPosition(x, y);
}


Heart::Heart(float x, float y, const VideoMode& vm)
{
	this->initTexture();
	this->initSprite(x, y, vm);
}

Heart::~Heart()
{

}


void Heart::update()
{
	
}

void Heart::render(RenderTarget* target)
{
	target->draw(this->heart);
}
