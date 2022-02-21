#ifndef STATE_H
#define STATE_H

#include "GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
	RenderWindow* window;
	GraphicsSettings* gfxSettings;
	map<string, int>* supportedKeys;
	stack<State*>* states;
};

class State
{
private:


protected:
	StateData* stateData;
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

	//map<string, Texture> textures;

	virtual void initKeybinds() = 0;

public:
	State(StateData* stateData);
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