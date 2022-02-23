#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "ControlState.h"
#include "SettingState.h"
#include "CreditsState.h"
#include "Gui.h"

class MainMenuState :
    public State
{
private:
    Texture backgroundTexture;
    RectangleShape background;
    Font font;
    Text topic;

    map<string, gui::Button*> buttons;

    void initVariables();
    void initFonts();
    void initKeybinds();
    void initGui();

public:
    MainMenuState(StateData* stateData);
    virtual ~MainMenuState();

    void updateInput(const float& dt);
    void updateGui();
    void update(const float& dt);
    void renderGui(RenderTarget& target);
    void render(RenderTarget* target = NULL);
};

#endif