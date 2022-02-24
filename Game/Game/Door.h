#ifndef DOOR_H
#define DOOR_H

#include "Gui.h"

class Door
{
private:
    RectangleShape door;
    Texture textureSheet;
    IntRect currentFrame;

    void initTexture();
    void initSprite(float x, float y, const VideoMode& vm);

public:
    Door(float x, float y, const VideoMode& vm);
    virtual ~Door();

    const Vector2f getGlobalBounds() const;
    const Vector2f getPos();

    void update();
    void render(RenderTarget* target);
};

#endif