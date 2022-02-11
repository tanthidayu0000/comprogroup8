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
	ifstream ifs("Config/creditsstate_keybinds.ini");

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

void CreditsState::initGui()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(72.9f, vm), gui::p2pY(88.f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		Color(200, 200, 200, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->credit.setFont(font);
	this->credit.setString("Credits");
	this->credit.setCharacterSize(gui::calcCharSize(vm, 20));
	this->credit.setOrigin(
		this->credit.getLocalBounds().left + this->credit.getLocalBounds().width / 2.f,
		this->credit.getLocalBounds().top + this->credit.getLocalBounds().height / 2.f
	);
	this->credit.setPosition(Vector2f(gui::p2pX(50.f, vm), gui::p2pY(20.f, vm)));
	this->credit.setFillColor(Color(255, 255, 255, 200));

	this->name1.setFont(font);
	this->name1.setString("Thidayu Peaungtham");
	this->name1.setCharacterSize(gui::calcCharSize(vm, 50));
	this->name1.setOrigin(
		this->name1.getLocalBounds().left + this->name1.getLocalBounds().width / 2.f,
		this->name1.getLocalBounds().top + this->name1.getLocalBounds().height / 2.f
	);
	this->name1.setPosition(Vector2f(gui::p2pX(50.f, vm), gui::p2pY(40.f, vm)));
	this->name1.setFillColor(Color(255, 255, 255, 200));

	this->name2.setFont(font);
	this->name2.setString("Thanaporn Chanchanayothin");
	this->name2.setCharacterSize(gui::calcCharSize(vm, 50));
	this->name2.setOrigin(
		this->name2.getLocalBounds().left + this->name2.getLocalBounds().width / 2.f,
		this->name2.getLocalBounds().top + this->name2.getLocalBounds().height / 2.f
	);
	this->name2.setPosition(Vector2f(gui::p2pX(50.f, vm), gui::p2pY(50.f, vm)));
	this->name2.setFillColor(Color(255, 255, 255, 200));

	this->name3.setFont(font);
	this->name3.setString("Sawit Charuekpoonpol");
	this->name3.setCharacterSize(gui::calcCharSize(vm, 50));
	this->name3.setOrigin(
		this->name3.getLocalBounds().left + this->name3.getLocalBounds().width / 2.f,
		this->name3.getLocalBounds().top + this->name3.getLocalBounds().height / 2.f
	);
	this->name3.setPosition(Vector2f(gui::p2pX(50.f, vm), gui::p2pY(60.f, vm)));
	this->name3.setFillColor(Color(255, 255, 255, 200));

	this->name4.setFont(font);
	this->name4.setString("Tipanan Jinathong");
	this->name4.setCharacterSize(gui::calcCharSize(vm, 50));
	this->name4.setOrigin(
		this->name4.getLocalBounds().left + this->name4.getLocalBounds().width / 2.f,
		this->name4.getLocalBounds().top + this->name4.getLocalBounds().height / 2.f
	);
	this->name4.setPosition(Vector2f(gui::p2pX(50.f, vm), gui::p2pY(70.f, vm)));
	this->name4.setFillColor(Color(255, 255, 255, 200));
}

CreditsState::CreditsState(StateData* stateData)
	: State(stateData)
{
	this->innitVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
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
	
}

void CreditsState::updateGui()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}
}

void CreditsState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->updateGui();
}

void CreditsState::renderGui(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(*target);
	}
}

void CreditsState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->credit);
	target->draw(this->name1);
	target->draw(this->name2);
	target->draw(this->name3);
	target->draw(this->name4);

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