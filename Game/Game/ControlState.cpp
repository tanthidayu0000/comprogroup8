#include "includeAll.h"
#include "ControlState.h"

void ControlState::innitVariables()
{

}

void ControlState::initBackground()
{

}

void ControlState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/DM Weekend Regular.ttf"))
	{
		throw("ERROR::EDITORSTATE::CLOUD NOT LOAD FONT");
	}
}

void ControlState::initKeybinds()
{
	ifstream ifs("Config/controlstate_keybinds.ini");

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

void ControlState::initGui()
{

}

ControlState::ControlState(StateData* stateData)
	: State(stateData)
{
	this->innitVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

ControlState::~ControlState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void ControlState::updateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void ControlState::updateGui()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
}

void ControlState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->updateGui();
}

void ControlState::renderGui(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(*target);
	}
}

void ControlState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderGui(target);

	/*Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(24);
	stringstream ss;
	ss << this->mousePosView.x << " , " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}