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

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/DM Weekend Regular.ttf"))
	{
		throw("ERROR::MIANMENUSTATE::CLOUD NOT LOAD FONT");
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("RESUME", 500.f, "Resume");
	this->pmenu->addButton("QUIT", 600.f, "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player();
}

GameState::GameState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
	this->initFonts();
	this->initPauseMenu();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
}

void GameState::updateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_LEFT"))));
		//this->player->animState(MOVE_LEFT);
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))));
		//this->player->animState(MOVE_RIGHT);
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("JUMPING"))));
		//this->player->animState(JUMPING);
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("FALLING"))));
		//this->player->animState(FALLING);
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

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
	
	if (this->pmenu->isButtonPressed("RESUME"))
		this->unpauseState();
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);
	this->updateInput(dt);
	
	if (!this->paused)
	{
		this->updatePlayerInput(dt);

		this->player->update();
		this->updateCollision();
	}
	else
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
	
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->player->render(this->window);

	if (this->paused)
	{
		this->pmenu->render(*target);
	}
}
