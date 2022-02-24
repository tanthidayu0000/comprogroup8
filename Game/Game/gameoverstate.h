#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "includeAll.h"
#include "State.h"
#include "Gui.h"
class Gameover :
	public State
{
private:
	Font font;
	Text menu;
	map<string, gui::Button*> buttons;
	Texture backg;
	RectangleShape background;

	void initGui();
	void initKeybinds();

public:


	Gameover(StateData* stateData);
	virtual ~Gameover();

	void updateInput(const float& dt);
	void updateGui();

	void update(const float& dt);

	void renderGui(RenderTarget& target);
	void render(RenderTarget* target);
};

#endif 
