#ifndef PLAYER_H
#define PLAYER_H

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
    void initSprite(float x, float y, float width, float height);
    void initAnimations();
    void initPhysics();

public:
    Player(float x, float y, float width, float height);
    virtual ~Player();

    const Vector2f getGlobalBounds() const;

    bool on_Ground();
    const Vector2f getPos();

    void setPosition(const float x, const float y);
    void resetVelocityY();
    void resetVelocityX();

    void move(const float dir_x, const float dir_y);
    void updatePhysics();
    void updateMovement();
    void updateAnimations();
    void update();
    void render(RenderTarget* target);
};

#endif