#include "includeAll.h"
#include "GameState.h"

void GameState::initKeybinds()
{
	ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		string key = "";
		string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initPlayers()
{
	this->player = new Player();
}

GameState::GameState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->player;
}

void GameState::updateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_LEFT"))));
	//this->player->
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))));
	//this->player->
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("JUMPING"))));
	//this->player->
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("FALLING"))));
		//this->player->

	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();

}

void GameState::updateCollision()
{
	if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height > this->window->getSize().y)
	{
		this->player->resetVelocityY();
		this->player->setPosition
		(
			this->player->getGlobalBounds().left,
			this->window->getSize().y - this->player->getGlobalBounds().height
		);
	}
	if (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width > this->window->getSize().x)
	{
		this->player->resetVelocityX();
		this->player->setPosition
		(
			this->window->getSize().x - this->player->getGlobalBounds().width,
			this->player->getGlobalBounds().top
		);
	}
	if (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width < this->player->getGlobalBounds().width)
	{
		this->player->resetVelocityX();
		this->player->setPosition
		(
			0.f,
			this->player->getGlobalBounds().top
		);
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->player->update();
	this->updateCollision();
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->player->render(this->window);
}
