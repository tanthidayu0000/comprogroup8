#include "includeAll.h"
#include "gameoverstate.h"

void Gameover::initGui()
{
	const VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->backg.loadFromFile("Background/midnight.jpg");
	this->background.setSize(
		Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setTexture(&this->backg);

	if (!font.loadFromFile("Fonts/Friday.ttf"))
	{

	}
	menu.setFont(font);
	menu.setCharacterSize(gui::calcCharSize(vm, 15));
	menu.setFillColor(Color::White);
	menu.setString("GAME OVER");
	menu.setOrigin(menu.getLocalBounds().width / 2, menu.getLocalBounds().height / 2);
	menu.setPosition(Vector2f(vm.width / 2, vm.height / 3));

	this->buttons["MAINMENU"] = new gui::Button(
		gui::p2pX(45.f, vm), gui::p2pY(60.f, vm),
		gui::p2pX(10.4f, vm), gui::p2pY(7.4f, vm),
		&this->font, "BACK TO MENU", gui::calcCharSize(vm, 40),
		Color(Color::White), Color(Color::Red), Color(20, 20, 20, 50),
		Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0));

}

void Gameover::initKeybinds()
{

}

Gameover::Gameover(StateData* stateData)
	: State(stateData)
{
	this->initKeybinds();
	this->initGui();
}

Gameover::~Gameover()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void Gameover::updateGui()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["MAINMENU"]->isPressed())
	{
		this->endState();
	}
}

void Gameover::updateInput(const float& dt)
{

}

void Gameover::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->updateGui();
}

void Gameover::renderGui(RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void Gameover::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->menu);

	this->renderGui(*target);
}

