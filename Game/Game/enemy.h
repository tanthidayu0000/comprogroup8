#ifndef ENEMY_H
#define ENEMY_H

class Enemy
{
private:
    ////Mouse positions
    /*Vector2i mousePosWindow;
    Vector2f mousePosView;*/

    //Game logic
    int points;
    float enemySpawnTimer;
    float enemySpawnTImerMax;
    int maxEnemies;

    Vector2f position;

    //Game objects
    Texture textureSheet;
    vector<RectangleShape> enemies;
    RectangleShape enemy;

    //Private functions
    void initVariables(const float time);
    void initEnemies(float width, float height);
public:
    //Constructors / Destructors
    Enemy(const float time, float width, float height);
    virtual ~Enemy();

    const Vector2f getGlobalBounds() const;
    const Vector2f getPos();

    //Functions
    void spawnEnemy(const VideoMode& vm);
    //void updateMousePositions();
    void update(const VideoMode& vm);
    void render(RenderTarget* target);
};

#endif