#ifndef CONTROLSTATE_H
#define CONTROLSTATE_H

#include "State.h"
#include "Gui.h"

class ControlState :
    public State
{
private:
    Font font;
    Font symbol;

    map<string, gui::Button*> buttons;

    Text control;
    Text move;
    Text or_;
    Text pause;
    Text puzzle;

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