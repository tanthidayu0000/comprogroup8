#include "includeAll.h"
#include "Playagainstate.h"

void Playagain::initGui()
{
	this->buttons["RESTART"] = new gui::Button(
		gui::p2pX(25.f, this->vm), gui::p2pY(60.f, this->vm),
		gui::p2pX(16.5f, this->vm), gui::p2pY(7.4f, this->vm),
		&this->font, "RESTART", gui::calcCharSize(this->vm, 40),
		Color(Color(255, 153, 0)), Color(Color::Red), Color(20, 20, 20, 50),
		Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0));

	this->buttons["QUIT"] = new gui::Button(
		gui::p2pX(65.f, this->vm), gui::p2pY(60.f, this->vm),
		gui::p2pX(10.4f, this->vm), gui::p2pY(7.4f, this->vm),
		&this->font, "QUIT", gui::calcCharSize(this->vm, 40),
		Color(Color(255, 153, 0)), Color(Color::Red), Color(20, 20, 20, 50),
		Color(0, 0, 0, 0), Color(0, 0, 0, 0), Color(0, 0, 0, 0));
}

Playagain::Playagain(float width, float height, const VideoMode& vm)
	: Map(width, height, vm)
{
	this->backg.loadFromFile("Background/sky.jpg");
	this->background.setSize(
		Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setTexture(&this->backg);

	if (!font.loadFromFile("Fonts/alagard.ttf"))
	{

	}
	menu.setFont(font);
	menu.setCharacterSize(gui::calcCharSize(vm, 20));
	menu.setFillColor(Color(255, 153, 0));
	menu.setString("MISSION COMPLETED");
	menu.setOrigin(menu.getLocalBounds().width / 2, menu.getLocalBounds().height / 2);
	menu.setPosition(Vector2f(width / 2, height / 3));

	this->initGui();
}

Playagain::~Playagain()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

bool Playagain::gameover()
{
	return false;
}

void Playagain::updateGui(Vector2f mouseposview)
{
	for (auto& it : this->buttons)
	{
		it.second->update(mouseposview);
	}

	if (this->buttons["RESTART"]->isPressed())
	{
		this->restart = true;
	}

	if (this->buttons["QUIT"]->isPressed())
	{
		this->endState();
	}
}

void Playagain::update(Vector2f mouseposview, RenderWindow* window)
{
	this->updateGui(mouseposview);
}

void Playagain::renderGui(RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void Playagain::render(RenderTarget* window)
{
	window->draw(this->background);
	window->draw(this->menu);
	this->renderGui(*window);
}
