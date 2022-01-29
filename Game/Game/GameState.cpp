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

GameState::GameState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initKeybinds();
}

GameState::~GameState()
{

}

void GameState::endState()
{
	cout << "Ending GameState\n";
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();

	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player.move(dt, -1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player.move(dt, 1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player.move(dt, 0.f, -1.f);
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player.move(dt, 0.f, 1.f);
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->player.update(dt);
}

void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->player.render(this->window);
}
