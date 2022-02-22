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
	if (!this->font.loadFromFile("Fonts/PatrickHand-Regular.ttf"))
	{
		throw("ERROR::EDITORSTATE::CLOUD NOT LOAD FONT");
	}

	if (!this->symbol.loadFromFile("Fonts/SirucaPictograms.ttf"))
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
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(72.9f, vm), gui::p2pY(88.f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		Color(200, 200, 200, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));

	this->control.setFont(font);
	this->control.setString("Control");
	this->control.setCharacterSize(gui::calcCharSize(vm, 20));
	this->control.setOrigin(
		this->control.getLocalBounds().left + this->control.getLocalBounds().width / 2.f,
		this->control.getLocalBounds().top + this->control.getLocalBounds().height / 2.f
	);
	this->control.setPosition(Vector2f(gui::p2pX(50.f, vm), gui::p2pY(20.f, vm)));
	this->control.setFillColor(Color(255, 255, 255, 200));

	this->move.setFont(font);
	this->move.setPosition(Vector2f(gui::p2pX(25.f, vm), gui::p2pY(40.f, vm)));
	this->move.setCharacterSize(gui::calcCharSize(vm));
	this->move.setFillColor(Color(255, 255, 255, 200));
	this->move.setString("Move");

	this->buttons["W"] = new gui::Button(
		gui::p2pX(45.f, vm), gui::p2pY(40.f, vm),
		gui::p2pX(3.f, vm), gui::p2pY(5.3f, vm),
		&this->font, "W", gui::calcCharSize(vm),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200)
	);
	this->buttons["A"] = new gui::Button(
		gui::p2pX(42.f, vm), gui::p2pY(45.4f, vm),
		gui::p2pX(3.f, vm), gui::p2pY(5.3f, vm),
		&this->font, "A", gui::calcCharSize(vm),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200)
	);
	this->buttons["S"] = new gui::Button(
		gui::p2pX(45.f, vm), gui::p2pY(45.4f, vm),
		gui::p2pX(3.f, vm), gui::p2pY(5.3f, vm),
		&this->font, "S", gui::calcCharSize(vm),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200)
	);
	this->buttons["D"] = new gui::Button(
		gui::p2pX(48.f, vm), gui::p2pY(45.4f, vm),
		gui::p2pX(3.f, vm), gui::p2pY(5.3f, vm),
		&this->font, "D", gui::calcCharSize(vm),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200)
	);

	this->or_.setFont(font);
	this->or_.setPosition(Vector2f(gui::p2pX(55.f, vm), gui::p2pY(43.f, vm)));
	this->or_.setCharacterSize(gui::calcCharSize(vm));
	this->or_.setFillColor(Color(255, 255, 255, 200));
	this->or_.setString("Or");

	this->buttons["UP"] = new gui::Button(
		gui::p2pX(63.f, vm), gui::p2pY(40.f, vm),
		gui::p2pX(3.f, vm), gui::p2pY(5.3f, vm),
		&this->symbol, "^", gui::calcCharSize(vm),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200)
	);
	this->buttons["LEFT"] = new gui::Button(
		gui::p2pX(60.f, vm), gui::p2pY(45.4f, vm),
		gui::p2pX(3.f, vm), gui::p2pY(5.3f, vm),
		&this->symbol, "<", gui::calcCharSize(vm),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200)
	);
	this->buttons["DOWN"] = new gui::Button(
		gui::p2pX(63.f, vm), gui::p2pY(45.4f, vm),
		gui::p2pX(3.f, vm), gui::p2pY(5.3f, vm),
		&this->symbol, "|", gui::calcCharSize(vm),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200)
	);
	this->buttons["RIGHT"] = new gui::Button(
		gui::p2pX(66.f, vm), gui::p2pY(45.4f, vm),
		gui::p2pX(3.f, vm), gui::p2pY(5.3f, vm),
		&this->symbol, ">", gui::calcCharSize(vm),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200)
	);

	this->pause.setFont(font);
	this->pause.setPosition(Vector2f(gui::p2pX(25.f, vm), gui::p2pY(60.f, vm)));
	this->pause.setCharacterSize(gui::calcCharSize(vm));
	this->pause.setFillColor(Color(255, 255, 255, 200));
	this->pause.setString("Pause");

	this->buttons["P"] = new gui::Button(
		gui::p2pX(45.f, vm), gui::p2pY(60.f, vm),
		gui::p2pX(3.f, vm), gui::p2pY(5.3f, vm),
		&this->font, "P", gui::calcCharSize(vm),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200)
	);

	this->puzzle.setFont(font);
	this->puzzle.setPosition(Vector2f(gui::p2pX(25.f, vm), gui::p2pY(80.f, vm)));
	this->puzzle.setCharacterSize(gui::calcCharSize(vm));
	this->puzzle.setFillColor(Color(255, 255, 255, 200));
	this->puzzle.setString("Open Box / Door");

	this->buttons["ENTER"] = new gui::Button(
		gui::p2pX(42.f, vm), gui::p2pY(80.f, vm),
		gui::p2pX(9.f, vm), gui::p2pY(5.5f, vm),
		&this->font, "Enter", gui::calcCharSize(vm),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0),
		Color(255, 255, 255, 200), Color(255, 255, 255, 200), Color(255, 255, 255, 200)
	);
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
	
}

void ControlState::updateGui()
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

	target->draw(this->control);
	target->draw(this->move);
	target->draw(this->or_);
	target->draw(this->pause);
	target->draw(this->puzzle);

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