#include "includeAll.h"
#include "Game.h"

void Game::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
	this->dt = 0;
}

void Game::initWindow()
{
	ifstream ifs("Config/window.ini");
	this->videoModes = VideoMode::getFullscreenModes();

	string title = "None";
	VideoMode window_bounds = VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framrate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open())
	{
		getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framrate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}

	ifs.close();

	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;

	if(this->fullscreen)
		this->window = new RenderWindow(window_bounds, title, Style::Fullscreen | Style::Titlebar | Style::Close, windowSettings);
	else
		this->window = new RenderWindow(window_bounds, title, Style::Titlebar | Style::Close, windowSettings);

	this->window->setFramerateLimit(framrate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
	ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

	for (auto i : this->supportedKeys)
		cout << i.first << " " << i.second << "\n";
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

Game::Game()
{
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::endApplication()
{
	cout << "Ending Application\n";
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();

}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
