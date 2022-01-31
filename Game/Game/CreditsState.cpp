#include "includeAll.h"
#include "CreditsState.h"

void CreditsState::innitVariables()
{

}

void CreditsState::initBackground()
{
	
}

void CreditsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/DM Weekend Regular.ttf"))
	{
		throw("ERROR::EDITORSTATE::CLOUD NOT LOAD FONT");
	}
}

void CreditsState::initKeybinds()
{
	ifstream ifs("Config/editorstate_keybinds.ini");

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

void CreditsState::initButtons()
{
	
}

CreditsState::CreditsState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->innitVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

CreditsState::~CreditsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void CreditsState::updateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void CreditsState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
}

void CreditsState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->updateButtons();
}

void CreditsState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void CreditsState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

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