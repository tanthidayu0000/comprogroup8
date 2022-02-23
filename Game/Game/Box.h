#ifndef BOX_H
#define BOX_H

#include "Gui.h"

class Box
{
private:
    RectangleShape box;
    Texture textureSheet;
    IntRect currentFrame;
    bool open;

    void initTexture();
    void initSprite(float x, float y, const VideoMode& vm);

public:
	Box(float x, float y, const VideoMode& vm);
	virtual ~Box();

    const Vector2f getGlobalBounds() const;
    const Vector2f getPos();

    bool openbox();
    void update();
    void render(RenderTarget* target);
};

#endif