#ifndef CONTROLSTATE_H
#define CONTROLSTATE_H

#include "State.h"
#include "Gui.h"

class ControlState :
    public State
{
private:
    Font font;

    map<string, gui::Button*> buttons;

    void innitVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();

public:
    ControlState(StateData* stateData);
    virtual ~ControlState();

    void updateInput(const float& dt);
    void updateGui();
    void update(const float& dt);
    void renderGui(RenderTarget* target = NULL);
    void render(RenderTarget* target = NULL);
};

#endif