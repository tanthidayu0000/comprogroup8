#ifndef PLAYAGAIN_H
#define PLAYAGAIN_H
#include "includeAll.h"
#include "Map.h"
#include "Gui.h"
class Playagain :
	 public Map
{
private:
	Font font;
	Text menu;
	map<string, gui::Button*> buttons;
	Texture backg;
	RectangleShape background;

	void initGui();

public:
	

	Playagain(float width, float height, const VideoMode& vm);
	virtual ~Playagain();

	void updateGui(Vector2f mouseposview);
	void update(Vector2f mouseposview);

	void renderGui(RenderTarget& target);
	void render(RenderTarget* window);

};

#endif 


