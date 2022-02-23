#ifndef COIN_H
#define COIN_H

#include "Gui.h"

class Coin
{
private:
    RectangleShape coin;
    Texture textureSheet;
    IntRect currentFrame;

    Clock animationTimer;

    void initTexture();
    void initSprite(float x, float y, const VideoMode& vm);
    void initAnimations();

public:
    Coin(float x, float y, const VideoMode& vm);
    virtual ~Coin();

    const Vector2f getGlobalBounds() const;
    const Vector2f getPos();

    void update();
    void render(RenderTarget* target);
};

#endif