#ifndef HEART_H
#define HEART_H

#include "Gui.h"

class Heart
{
private:
    RectangleShape heart;
    Texture textureSheet;


    void initTexture();
    void initSprite(float x, float y, const VideoMode& vm);

public:
    Heart(float x, float y, const VideoMode& vm);
    virtual ~Heart();


    void update();
    void render(RenderTarget* target);
};

#endif