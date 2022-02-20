#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include "State.h"
#include "Gui.h"

class CreditsState :
    public State
{
private:
    Font font;

    map<string, gui::Button*> buttons;

    Text credit;
    Text name1;
    Text name2;
    Text name3;
    Text name4;


    void innitVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();

public:
    CreditsState(StateData* stateData);
    virtual ~CreditsState();

    void updateInput(const float& dt);
    void updateGui();
    void update(const float& dt);
    void renderGui(RenderTarget* target = NULL);
    void render(RenderTarget* target = NULL);
};

#endif