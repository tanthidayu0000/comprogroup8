#include "includeAll.h"
#include "GameState.h"

void GameState::initVariables()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->background.setSize(
		Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Background/bgMap.png"))
		throw "ERROR::GAME_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	this->background.setTexture(&this->backgroundTexture);
}

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
	if (!this->font.loadFromFile("Fonts/PatrickHand-Regular.ttf"))
	{
		throw("ERROR::MIANMENUSTATE::CLOUD NOT LOAD FONT");
	}
}

void GameState::initPauseMenu()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("RESUME", gui::p2pY(47.2f, vm), gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm), gui::calcCharSize(vm), "Resume");
	this->pmenu->addButton("QUIT", gui::p2pY(54.6f, vm), gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initMap()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->map1 = new Map1(gui::p2pX(2.5f, vm), gui::p2pY(4.45f, vm));
}

void GameState::initPlayers()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->player = new Player(gui::p2pX(0.f, vm), gui::p2pY(88.8f, vm), gui::p2pX(2.5f, vm), gui::p2pY(4.4f, vm));
}

void GameState::initEnemy()
{
	this->enemy = new Enemy();
}

GameState::GameState(StateData* stateData)
	: State(stateData)
{
	this->initVariables();
	this->initKeybinds();
	this->initFonts();
	this->initPauseMenu();
	this->initMap();
	this->initPlayers();
	this->initEnemy();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->map1;
	delete this->player;
	delete this->enemy;
}

void GameState::updateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("PAUSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

//void GameState::updatePlayerInput()
//{
//	this->player->animationState(IDLE);
//
//	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVING_LEFT"))) || Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_LEFT"))));
//		this->player->animationState(MOVE_LEFT);
//	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVING_RIGHT"))) || Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))));
//		this->player->animationState(MOVE_RIGHT);
//	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("JUMPING"))) || Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("JUMP"))));
//		this->player->animationState(JUMPING);
//	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("FALLING"))) || Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("FALL"))));
//		this->player->animationState(FALLING);
//}

void GameState::updateCollision()
{
	if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height > this->map1->getPos())
	{
		this->player->resetVelocityY();
		this->player->setPosition
		(
			this->player->getGlobalBounds().left,
			this->map1->getPos() - this->player->getGlobalBounds().height
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
	if (this->pmenu->isButtonPressed("RESUME"))
		this->unpauseState();

	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);
	this->updateInput(dt);
	
	if (!this->paused)
	{
		//this->updatePlayerInput();
		this->map1->update();
		this->player->update();
		this->enemy->update(this->window);
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
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	if (!target)
		target = this->window;

	target->draw(this->background);

	this->map1->render(target, gui::p2pX(2.5f, vm), gui::p2pY(4.45f, vm));
	this->player->render(target);
	this->enemy->render(target);

	if (this->paused)
	{
		this->pmenu->render(*target);
	}
}
