#include "includeAll.h"
#include "SettingState.h"

void SettingState::innitVariables()
{
	this->modes = VideoMode::getFullscreenModes();
}

void SettingState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/PatrickHand-Regular.ttf"))
	{
		throw("ERROR::MIANMENUSTATE::CLOUD NOT LOAD FONT");
	}
}

void SettingState::initKeybinds()
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

void SettingState::initGui()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->background.setSize(
		Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Background/MainMenu.jpeg"))
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";

	this->background.setTexture(&this->backgroundTexture);

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(72.9f, vm), gui::p2pY(88.f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		Color(200, 200, 200, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(
		gui::p2pX(62.5f, vm), gui::p2pY(88.f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm),
		&this->font, "Apply", gui::calcCharSize(vm),
		Color(200, 200, 200, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	vector<string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(to_string(i.width) + 'x' + to_string(i.height));
	}
	this->dropDownList["4RESOLUTION"] = new gui::DropDownList(
		gui::p2pX(30.2f, vm), gui::p2pY(44.3f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(2.3f, vm),
		font, modes_str.data(), modes_str.size()
	);

	vector<string> fulls;
	if (this->stateData->gfxSettings->fullscreen)
		fulls = { "ON", "OFF" };
	else
		fulls = { "OFF", "ON" };
	this->dropDownList["1FULLSCREEN"] = new gui::DropDownList(
		gui::p2pX(30.2f, vm), gui::p2pY(57.8f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(2.3f, vm),
		font, fulls.data(), fulls.size()
	);

	vector<string> vsync;
	if (this->stateData->gfxSettings->verticalSync)
		vsync = { "ON", "OFF" };
	else
		vsync = { "OFF", "ON" };
	this->dropDownList["2VSYNC"] = new gui::DropDownList(
		gui::p2pX(30.2f, vm), gui::p2pY(72.f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(2.3f, vm),
		font, vsync.data(), vsync.size()
	);

	vector<string> anti;
	if (this->stateData->gfxSettings->contextSettings.antialiasingLevel)
		anti = { "ON", "OFF" };
	else
		anti = { "OFF", "ON" };
	this->dropDownList["3ANTI"] = new gui::DropDownList(
		gui::p2pX(30.2f, vm), gui::p2pY(85.7f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(2.3f, vm),
		font, anti.data(), anti.size()
	);

	this->Resolution.setFont(font);
	this->Resolution.setPosition(Vector2f(gui::p2pX(10.4f, vm), gui::p2pY(41.7f, vm)));
	this->Resolution.setCharacterSize(gui::calcCharSize(vm, 60));
	this->Resolution.setFillColor(Color(255, 255, 255, 200));
	this->Resolution.setString("Resolution");

	this->Fullscreen.setFont(font);
	this->Fullscreen.setPosition(Vector2f(gui::p2pX(10.4f, vm), gui::p2pY(55.5f, vm)));
	this->Fullscreen.setCharacterSize(gui::calcCharSize(vm, 60));
	this->Fullscreen.setFillColor(Color(255, 255, 255, 200));
	this->Fullscreen.setString("Fullscreen");

	this->Vsync.setFont(font);
	this->Vsync.setPosition(Vector2f(gui::p2pX(10.4f, vm), gui::p2pY(69.4f, vm)));
	this->Vsync.setCharacterSize(gui::calcCharSize(vm, 60));
	this->Vsync.setFillColor(Color(255, 255, 255, 200));
	this->Vsync.setString("Vsync");

	this->Antialiasing.setFont(font);
	this->Antialiasing.setPosition(Vector2f(gui::p2pX(10.4f, vm), gui::p2pY(83.3f, vm)));
	this->Antialiasing.setCharacterSize(gui::calcCharSize(vm, 60));
	this->Antialiasing.setFillColor(Color(255, 255, 255, 200));
	this->Antialiasing.setString("Antialiasing");
}

void SettingState::resetGui()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	auto it2 = this->dropDownList.begin();
	for (it2 = this->dropDownList.begin(); it2 != this->dropDownList.end(); ++it2)
	{
		delete it2->second;
	}
	this->dropDownList.clear();

	this->initGui();
}

SettingState::SettingState(StateData* stateData)
	:State(stateData)
{
	this->innitVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
}

SettingState::~SettingState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	auto it2 = this->dropDownList.begin();
	for (it2 = this->dropDownList.begin(); it2 != this->dropDownList.end(); ++it2)
	{
		delete it2->second;
	}
}

void SettingState::updateInput(const float& dt)
{

}

void SettingState::updateGui(const float& dt)
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["BACK"]->isPressed())
	{
		this->states->push(new MainMenuState(this->stateData));
		
		this->endState();
	}

	if (this->buttons["APPLY"]->isPressed())
	{
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownList["4RESOLUTION"]->getActiveElementId()];

		if (this->dropDownList["1FULLSCREEN"]->getActiveElementText() == "ON")
			this->stateData->gfxSettings->fullscreen = true;
		else
			this->stateData->gfxSettings->fullscreen = false;

		if (this->dropDownList["2VSYNC"]->getActiveElementText() == "ON")
			this->stateData->gfxSettings->verticalSync = true;
		else
			this->stateData->gfxSettings->verticalSync = false;

		if (this->dropDownList["3ANTI"]->getActiveElementText() == "ON")
			this->stateData->gfxSettings->contextSettings.antialiasingLevel = true;
		else
			this->stateData->gfxSettings->contextSettings.antialiasingLevel = false;

		if (this->stateData->gfxSettings->fullscreen)
		{
			this->stateData->gfxSettings->resolution.width = 1920;
			this->stateData->gfxSettings->resolution.height = 1080;
			this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, Style::Fullscreen);
			this->window->setFramerateLimit(this->stateData->gfxSettings->frameRateLimit);
		}
		else
		{
			this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, Style::Default);
			this->window->setFramerateLimit(this->stateData->gfxSettings->frameRateLimit);
		}

		this->resetGui();
	}

	for (auto &it : this->dropDownList)
	{
		it.second->update(this->mousePosView, dt);
	}

}

void SettingState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->updateGui(dt);
}

void SettingState::renderGui(RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto &it : this->dropDownList)
	{
		it.second->render(target);
	}
}

void SettingState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	target->draw(this->Resolution);
	target->draw(this->Fullscreen);
	target->draw(this->Vsync);
	target->draw(this->Antialiasing);

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