#include "includeAll.h"
#include "Player.h"

void Player::initAnimState()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Sprites/Player/character1.png"))
	{
		cout << "ERROR::PLAYER::Cloud not load the player sheet!";
	}
}

void Player::initSprite()
{
	this->sprite.setTexture(this->textureSheet);
	this->currentFrame = IntRect(0, 0, 32, 32);

	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(1.5f, 1.5f);
	this->sprite.setPosition(0.f, 1000.f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
}

void Player::initPhysics()
{
	this->velocityMax = 2.5f;
	this->velocityMin = 1.f;
	this->acceleration = 2.f;
	this->drag = 0.93f;
	this->gravity = 4.f;
}

Player::Player()
{
	this->initAnimState();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{

}

const FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Player::resetVelocityX()
{
	this->velocity.x = 0.f;
}

void Player::move(const float dir_x, const float dir_y)
{
	this->velocity.x += dir_x * this->acceleration;

	if (abs(this->velocity.x) > this->velocityMax)
	{
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}
}

void Player::updatePhysics()
{
	this->velocity.y += 1.0 * this->gravity;
	if (this->velocity.y > this->gravity)
	{
		for (float i = this->gravity; i > 0; i -= 0.1f)
			this->velocity.y -= 0.01f;
	}

	this->velocity *= this->drag;

	if (abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

	this->sprite.move(this->velocity);
}

void Player::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;

	if (Keyboard::isKeyPressed(Keyboard::Key::A) || Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVE_LEFT;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D) || Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		this->move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVE_RIGHT;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::W) || Keyboard::isKeyPressed(Keyboard::Key::Up))
	{
		if (this->velocity.y != 0.f)
			this->onGround = false;
		else
			this->onGround = true;

		if (this->currentFrame.top == 0.f)
		{
			this->sprite.move(6.f, -20.f);
		}
		else if (this->currentFrame.top == 32.f)
		{
			this->sprite.move(-6.f, -20.f);
		}

		this->animState = PLAYER_ANIMATION_STATES::JUMPING;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S) || Keyboard::isKeyPressed(Keyboard::Key::Down))
	{
		if (this->velocity.y != 0.f)
			this->onGround = false;
		else
			this->onGround = true;

		this->sprite.move(0.f, 1.f);
		this->animState = PLAYER_ANIMATION_STATES::FALLING;
	}
}

void Player::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			if (this->currentFrame.top == 0.f)
				this->currentFrame.left = 0.f;
			else if (this->currentFrame.top == 32.f)
				this->currentFrame.left = 0.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVE_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 128.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVE_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 32.f;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 128.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::JUMPING)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			if (this->currentFrame.top == 0.f)
			{
				this->currentFrame.left = 32.f;
				if (this->onGround)
					this->currentFrame.left = 0;
			}
			else if (this->currentFrame.top == 32.f)
			{
				this->currentFrame.left = 32.f;
				if (this->onGround)
					this->currentFrame.left = 0;
			}

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::FALLING)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			if (this->currentFrame.top == 0.f)
			{
				this->currentFrame.left = 32.f;
				if (this->onGround)
					this->currentFrame.left = 0;
			}
			else if (this->currentFrame.top == 32.f)
			{
				this->currentFrame.left = 32.f;
				if (this->onGround)
					this->currentFrame.left = 0;
			}

			else
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Player::render(RenderTarget* target)
{
	target->draw(this->sprite);
}
