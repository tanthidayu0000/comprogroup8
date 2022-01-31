#include "includeAll.h"
#include "MainMenuState.h"

void MainMenuState::innitVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize
	(
		Vector2f
		(static_cast<float>(this->window->getSize().x), 
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Background/MainMenu.jpeg"))
		throw"ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/DM Weekend Regular.ttf"))
	{
		throw("ERROR::MIANMENUSTATE::CLOUD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	ifstream ifs("Config/mainmenustate_keybinds.ini");

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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(
		835.f, 700.f, 250.f, 100.f,
		&this->font, "Start", 60,
		Color(100, 100, 100, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->buttons["CREDITS_STATE"] = new Button(
		835.f, 800.f, 250.f, 100.f,
		&this->font, "Credits", 60,
		Color(100, 100, 100, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new Button(
		835.f, 900.f, 250.f, 100.f,
		&this->font, "Quit", 60,
		Color(100, 100, 100, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));
}

MainMenuState::MainMenuState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->innitVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	if (this->buttons["CREDITS_STATE"]->isPressed())
	{
		this->states->push(new CreditsState(this->window, this->supportedKeys, this->states));
	}

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(*target);
	}
}

void MainMenuState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);

	/*Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(24);
	stringstream ss;
	ss << this->mousePosView.x << " , " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}