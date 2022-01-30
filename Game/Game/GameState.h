#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState :
    public State
{
private:
    Player* player;

    void initKeybinds();
    void initPlayers();

public:
    GameState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~GameState();

    void updateInput(const float& dt);
    void updateCollision();
    void update(const float& dt);
    void render(RenderTarget* target = NULL);

};


#endif