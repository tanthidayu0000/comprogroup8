#ifndef STATE_H
#define STATE_H

#include "Player.h"

class State
{
private:


protected:
	stack<State*>* states;
	RenderWindow* window;
	map<string, int>* supportedKeys;
	map<string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;

	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	map<string, Texture> textures;

	virtual void initKeybinds() = 0;

public:
	State(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	const bool getKeytime();

	void endState();
	void pauseState();
	void unpauseState();
	
	virtual void updateMousePosition();
	virtual void updateKeyTime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = NULL) = 0;
};

#endif