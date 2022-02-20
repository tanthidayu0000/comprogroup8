#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "Map1.h"
#include "PauseMenu.h"

class GameState :
    public State
{
private:
    Texture backgroundTexture;
    RectangleShape background;

    Font font;
    PauseMenu* pmenu;

    Map1* map1;

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