#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	GraphicsSettings gfxSettings;
	StateData stateData;
	RenderWindow* window;
	Event sfEvent;

	Clock dtClock;
	float dt;

	stack<State*> states;

	map<string, int> supportedKeys;

	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();

public:
	Game();
	virtual ~Game();

	void endApplication();

	void updateDt();
	void updateSFMLEvents();
	void update();

	void render();

	void run();

};

#endif