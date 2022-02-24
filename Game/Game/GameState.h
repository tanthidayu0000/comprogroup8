#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Map1.h"
#include "Map2.h"
#include "Map3.h"
#include "PauseMenu.h"
#include "Playagainstate.h"
#include "gameoverstate.h"

class GameState :
    public State
{
private:
    Font font;
    PauseMenu* pmenu;

    stack<Map*> maps;


    void initVariables();
    void initKeybinds();
    void initFonts();
    void initPauseMenu();
    void initMap();



public:
    GameState(StateData* stateData);
    virtual ~GameState();
 

    void updateInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(RenderTarget* target = NULL);
};

#endif