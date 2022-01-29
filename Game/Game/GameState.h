#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "MainMenuState.h"

class GameState :
    public State
{
private:
    Entity player;

    void initKeybinds();

public:
    GameState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~GameState();

    void endState();

    void updateInput(const float& dt);
    void update(const float& dt);
    void render(RenderTarget* target = NULL);

};


#endif