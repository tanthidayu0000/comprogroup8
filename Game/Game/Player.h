#ifndef PLAYER_H
#define PLAYER_H

#include "Gui.h"

enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVE_LEFT, MOVE_RIGHT, JUMPING, FALLING };

class Player
{
private:
    RectangleShape sprite;
    Texture textureSheet;
    Clock animationTimer;

    short animState;
    IntRect currentFrame;

    bool onGround;
    Vector2f velocity;
    float velocityMax;
    float velocityMin;
    float acceleration;
    float drag;
    float gravity;

    void initAnimState();
    void initTexture();
    void initSprite(const VideoMode& vm);
    void initAnimations();
    void initPhysics(const VideoMode& vm);

public:
    Player(const VideoMode& vm);
    virtual ~Player();

    const Vector2f getVelocity();
    const Vector2f getGlobalBounds() const;
    const Vector2f getPos();

    void setPosition(const float x, const float y);
    void resetVelocityY();
    void resetVelocityX();

    void move(const float dir_x, const float dir_y);
    void updatePhysics();
    void updateMovement(const VideoMode& vm);
    void updateAnimations();
    void update(const VideoMode& vm);
    void render(RenderTarget* target);
};

#endif