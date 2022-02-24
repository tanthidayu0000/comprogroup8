#include "includeAll.h"
#include "MainMenuState.h"

void MainMenuState::initVariables()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->topic.setFont(this->font);
	this->topic.setCharacterSize(gui::calcCharSize(vm, 20));
	this->topic.setFillColor(Color(255, 255, 255, 200));
	this->topic.setString("MYSTERY WORLD");
	this->topic.setOrigin(this->topic.getGlobalBounds().width / 2, this->topic.getGlobalBounds().height / 2);
	this->topic.setPosition(Vector2f(gui::p2pX(50.f, vm), gui::p2pY(30.f, vm)));
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::CLOUD NOT LOAD FONT");
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

void MainMenuState::initGui()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->background.setSize(
		Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Background/wall.jpg"))
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	this->background.setTexture(&this->backgroundTexture);
	
	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2pX(30.f, vm), gui::p2pY(69.4f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm),
		&this->font, "Start", gui::calcCharSize(vm,65),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->buttons["CONTROL_STATE"] = new gui::Button(
		gui::p2pX(55.f, vm), gui::p2pY(69.4f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm),
		&this->font, "Control", gui::calcCharSize(vm,65),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->buttons["CREDITS_STATE"] = new gui::Button(
		gui::p2pX(30.f, vm), gui::p2pY(80.f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm),
		&this->font, "Credits", gui::calcCharSize(vm,65),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2pX(55.f, vm), gui::p2pY(80.f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm),
		&this->font, "Quit", gui::calcCharSize(vm,65),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	/*this->buttons["SETTING_STATE"] = new gui::Button(
		gui::p2pX(44.8f, vm), gui::p2pY(76.9f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm),
		&this->font, "Setting", gui::calcCharSize(vm),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->buttons["CREDITS_STATE"] = new gui::Button(
		gui::p2pX(44.8f, vm), gui::p2pY(84.3f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm),
		&this->font, "Credits", gui::calcCharSize(vm),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2pX(44.8f, vm), gui::p2pY(91.7f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm),
		&this->font, "Quit", gui::calcCharSize(vm),
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));*/
}

MainMenuState::MainMenuState(StateData* stateData)
	: State(stateData)
{
	this->initFonts();
	this->initVariables();
	this->initKeybinds();
	this->initGui();
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

void MainMenuState::updateGui()
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	if (this->buttons["CONTROL_STATE"]->isPressed())
	{
		this->states->push(new ControlState(this->stateData));
	}

	/*if (this->buttons["SETTING_STATE"]->isPressed())
	{
		this->states->pop();
		this->states->push(new SettingState(this->stateData));
	}*/

	if (this->buttons["CREDITS_STATE"]->isPressed())
	{
		this->states->push(new CreditsState(this->stateData));
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

	this->updateGui();
}

void MainMenuState::renderGui(RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->topic);

	this->renderGui(*target);

	/*Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 25);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(24);
	stringstream ss;
	ss << this->mousePosView.x << " , " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}