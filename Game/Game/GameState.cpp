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

	this->map1 = new Map1(gui::p2pX(2.5f, vm), gui::p2pY(4.45f, vm), vm);
}

GameState::GameState(StateData* stateData)
	: State(stateData)
{
	this->initVariables();
	this->initKeybinds();
	this->initFonts();
	this->initPauseMenu();
	this->initMap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->map1;
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
		this->map1->update();
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

	if (this->paused)
	{
		this->pmenu->render(*target);
	}

	/*Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 25);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(24);
	stringstream ss;
	ss << this->mousePosView.x << " , " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}
