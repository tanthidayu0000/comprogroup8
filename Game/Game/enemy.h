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

    //Game objects
    vector<RectangleShape> enemies;
    RectangleShape enemy;

    //Private functions
    void initVariables();
    void initEnemies();
public:
    //Constructors / Destructors
    Enemy();
    virtual ~Enemy();

    //Functions
    void spawnEnemy(const VideoMode& vm);
    //void updateMousePositions();
    void update(const VideoMode& vm);
    void render(RenderTarget* target);
};

#endif