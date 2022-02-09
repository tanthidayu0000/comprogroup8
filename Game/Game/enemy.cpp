#include "includeAll.h"
#include "Enemy.h"

//Private functions
void Enemy::initVariables()
{
    //Game logic
    this->points = 0;
    this->enemySpawnTImerMax = 200.f;
    this->enemySpawnTimer = this->enemySpawnTImerMax;
    this->maxEnemies = 10;
}

void Enemy::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(Vector2f(100.f, 100.f));
    this->enemy.setScale(Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(Color::Cyan);
    //this->enemy.setOutlineColor(Color::Green);
    //this->enemy.setOutlineThickness(1.f);
}

//Constructors / Destructors

Enemy::Enemy()
{
    this->initVariables();
    this->initEnemies();
}

Enemy::~Enemy()
{

}

// Functions
void Enemy::spawnEnemy(RenderTarget* target)
{
    /*
        @return void

        Spawns enemies and sets their color and positions.
        - sets a random position.
        - sets a random color.
        - adds enemy to the vector. 
    */

   this->enemy.setPosition(
       static_cast<float>(rand() % static_cast<int>(target->getSize().x - this->enemy.getSize().x)),
       static_cast<float>(rand() % static_cast<int>(target->getSize().y - this->enemy.getSize().y))
   );
   
   this->enemy.setFillColor(Color::Green);

    //Spawn the enemy
   this->enemies.push_back(this->enemy);
}

//void Enemy::updateMousePositions()
//{
//    /**
//        @return void
//
//        Updates the mouse positions:
//        - Mouse position relative to window (Vector2i)
//    */
//
//   this->mousePosWindow = Mouse::getPosition(*this->window);
//   this->mousePosView = this->window->mapPixelToCoords(this->mousePosView);
//}

void Enemy::update(RenderTarget* target)
{
    /**
        @return void

        Updates the enemy spawn timer and spawns enemies
        when the total amount of enemies is smaller than the maximum
        Moves the enemies downwards.
        Removes the enemies at the edge of the screen. /?TODO
     */

    //Updating the timer for enemy spawning
    if(this->enemies.size() < this->maxEnemies)
    {
        if(this->enemySpawnTimer >= this->enemySpawnTImerMax)
        {
            //Spawn the enemy and reset the timer
            this->spawnEnemy(target);
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    //Moving and updateing enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;

        this->enemies[i].move(0.f, 5.f);

        //Check if clicks upon
        //if(Mouse::isButtonPressed(Mouse::Left))
        //{
        //    if(this->enemies[i].getGlobalBounds().contains(this->mousePosView))
        //    {
        //        deleted = true;

        //        //Gain Points
        //        this->points += 10.f;
        //    }
        //}

        //If the enemy is past the bottom of the screen
        if(this->enemies[i].getPosition().y > target->getSize().y)
        {
            deleted = true;
        }

        //Final delete
        if(deleted)
            this->enemies.erase(this->enemies.begin() + i);
    }
}

void Enemy::render(RenderTarget* target)
{
    //Rendering all the enemies
    for (auto &e : this->enemies)
    {
        target->draw(e);
    }
}