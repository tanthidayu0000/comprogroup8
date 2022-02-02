#include "includeAll.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(RenderWindow& window, Font& font)
	: font(font)
{
	this->background.setSize(
		Vector2f(
			static_cast<float>(window.getSize().x), 
			static_cast<float>(window.getSize().y)
		)
	);
	this->background.setFillColor(Color(20, 20, 20, 100));

	this->container.setSize(
		Vector2f(
			static_cast<float>(window.getSize().x) / 4.f,
			static_cast<float>(window.getSize().y) / 3.f
		)
	);
	this->container.setFillColor(Color(20, 20, 20, 100));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		static_cast<float>(window.getSize().y) / 2.f - this->container.getSize().y / 2.f
	);

	this->menuText.setFont(font);
	this->menuText.setFillColor(Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(80);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getLocalBounds().width / 2.f,
		this->container.getPosition().y + 10.f
	);
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

map<string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

const bool PauseMenu::isButtonPressed(const string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const string key, float y, const string text)
{
	float width = 200.f;
	float height = 80.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	this->buttons[key] = new gui::Button(
		x, y, width, height,
		&this->font, text, 60,
		Color(100, 100, 100, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
		Color(100, 100, 100, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));
}

void PauseMenu::update(const Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::render(RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menuText);
}
