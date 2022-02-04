#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Gui.h"

class PauseMenu
{
private:
	Font& font;
	Text menuText;

	RectangleShape background;
	RectangleShape container;

	map<string, gui::Button*> buttons;

public:
	PauseMenu(VideoMode& vm, Font& font);
	virtual ~PauseMenu();

	map<string, gui::Button*>& getButtons();

	const bool isButtonPressed(const string key);
	void addButton(const string key,
		const float y, 
		const float width, const float height, 
		const unsigned charSize, 
		const string text);
	void update(const Vector2f& mousePos);
	void render(RenderTarget& target);
};

#endif