#include "includeAll.h"
#include "Coin.h"

void Coin::initTexture()
{
	if (!this->textureSheet.loadFromFile("Sprites/coin.png"))
	{
		cout << "ERROR::COIN::Cloud not load the coin sheet!";
	}
}

void Coin::initSprite(float x, float y, const VideoMode& vm)
{
	this->coin.setTexture(&this->textureSheet, true);
	this->currentFrame = IntRect(0, 0, 16, 16);

	this->coin.setTextureRect(this->currentFrame);
	this->coin.setSize(Vector2f(gui::p2pX(1.6f, vm), gui::p2pY(2.9f, vm)));
	this->coin.setPosition(x, y);
}

void Coin::initAnimations()
{
	this->animationTimer.restart();
}

Coin::Coin(float x, float y, const VideoMode& vm)
{
	this->initTexture();
	this->initSprite(x, y, vm);
	this->initAnimations();
}

Coin::~Coin()
{

}

const Vector2f Coin::getGlobalBounds() const
{
	return this->coin.getSize();
}

const Vector2f Coin::getPos()
{
	return this->coin.getPosition();
}

void Coin::update()
{
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
	{
		this->currentFrame.left += 16.f;

		if (this->currentFrame.left >= 64.f)
		{
			this->currentFrame.left = 0.f;
			this->animationTimer.restart();
			this->coin.setTextureRect(this->currentFrame);
		}
		else
		{
			this->animationTimer.restart();
			this->coin.setTextureRect(this->currentFrame);
		}
	}
}

void Coin::render(RenderTarget* target)
{
	target->draw(this->coin);
}
