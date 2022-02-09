#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"

class GameState :
    public State
{
private:
    Font font;
    PauseMenu* pmenu;

    Player* player;
    Enemy* enemy;

    void initKeybinds();
    void initFonts();
    void initPauseMenu();
    void initPlayers();
    void initEnemy();

public:
    GameState(StateData* stateData);
    virtual ~GameState();

    void updateInput(const float& dt);
    //void updatePlayerInput(const float& dt);
    void updateCollision();
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(RenderTarget* target = NULL);

};

#endif