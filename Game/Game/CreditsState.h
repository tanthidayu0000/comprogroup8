#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include "State.h"
#include "Button.h"

class CreditsState :
    public State
{
private:
    Font font;

    map<string, Button*> buttons;

    void innitVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    CreditsState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~CreditsState();

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(RenderTarget* target = NULL);
    void render(RenderTarget* target = NULL);
};

#endif