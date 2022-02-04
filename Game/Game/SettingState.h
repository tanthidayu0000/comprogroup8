#ifndef SETTINGSTATE_H
#define SETTINGSTATE_H

#include "State.h"
#include "MainMenuState.h"
#include "Gui.h"

class SettingState :
    public State
{
private:
    Texture backgroundTexture;
    RectangleShape background;
    Font font;

    map<string, gui::Button*> buttons;
    map<string, gui::DropDownList*> dropDownList;

    Text Resolution;
    Text Fullscreen;
    Text Vsync;
    Text Antialiasing;

    vector<VideoMode> modes;

    void innitVariables();
    void initFonts();
    void initKeybinds();
    void initGui();
    void resetGui();

public:
    SettingState(StateData* stateData);
    virtual ~SettingState();

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(RenderTarget& target);
    void render(RenderTarget* target = NULL);
};

#endif