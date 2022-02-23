#include "includeAll.h"
#include "Box.h"

void Box::initTexture()
{
	if (!this->textureSheet.loadFromFile("Sprites/box.png"))
	{
		cout << "ERROR::BOX::Cloud not load the box sheet!";
	}
}

void Box::initSprite(float x, float y, const VideoMode& vm)
{
	this->box.setTexture(&this->textureSheet, true);
	this->currentFrame = IntRect(0, 0, 32, 32);

	this->box.setTextureRect(this->currentFrame);
	this->box.setSize(Vector2f(gui::p2pX(2.5f, vm), gui::p2pY(4.45f, vm)));
	this->box.setPosition(x, y);
}

Box::Box(float x, float y, const VideoMode& vm)
{
	this->open = false;
	this->initTexture();
	this->initSprite(x, y, vm);
}

Box::~Box()
{

}

const Vector2f Box::getGlobalBounds() const
{
	return this->box.getSize();
}

const Vector2f Box::getPos()
{
	return this->box.getPosition();
}

bool Box::openbox()
{
	return this->open;
}

void Box::update()
{
	if (this->currentFrame.left == 0.f)
	{
		for (int i = 0; i < 3; i++)
		{
			this->currentFrame.left += 32.f;
			this->box.setTextureRect(this->currentFrame);
		}
	}
	this->open = true;
}

void Box::render(RenderTarget* target)
{
	target->draw(this->box);
}
