#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Button.h"

class EditorState :
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
    EditorState(RenderWindow* window, map<string, int>* supportedKeys, stack<State*>* states);
    virtual ~EditorState();

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(RenderTarget* target = NULL);
    void render(RenderTarget* target = NULL);
};

#endif