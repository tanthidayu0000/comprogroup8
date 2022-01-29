#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	RenderWindow* window;
	Event sfEvent;
	vector<VideoMode> videoModes;
	ContextSettings windowSettings;
	bool fullscreen;

	Clock dtClock;
	float dt;

	stack<State*> states;

	map<string, int> supportedKeys;

	void initVariables();
	void initWindow();
	void initKeys();
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