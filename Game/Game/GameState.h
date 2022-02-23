#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Map1.h"
#include "Map2.h"
#include "Map3.h"
#include "PauseMenu.h"
#include "Playagainstate.h"
#include "heart.h"

class GameState :
    public State
{
private:
    Font font;
    PauseMenu* pmenu;

    stack<Map*> maps;

    vector<Heart*> heart;

    void initVariables();
    void initKeybinds();
    void initFonts();
    void initPauseMenu();
    void initMap();

    void initHeart();

public:
    GameState(StateData* stateData);
    virtual ~GameState();

    void updateHeart();
    void updateInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(RenderTarget* target = NULL);
};

#endif