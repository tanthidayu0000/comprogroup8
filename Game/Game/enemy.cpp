#include "includeAll.h"
#include "Enemy.h"

//Private functions
void Enemy::initVariables(const float time)
{
    //Game logic
    this->points = 0;
    this->enemySpawnTImerMax = time;
    this->enemySpawnTimer = this->enemySpawnTImerMax;
    this->maxEnemies = 10;
}

void Enemy::initEnemies(float width, float height)
{
    if (!this->textureSheet.loadFromFile("Sprites/Enemy/Enemy1.png"))
    {
        cout << "ERROR::ENEMY::Cloud not load the enemy sheet!";
    }

    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(Vector2f(width, height));
    this->enemy.setTexture(&this->textureSheet);
    this->enemy.setTextureRect(IntRect(64, 0, 64, 192));
}

//Constructors / Destructors

Enemy::Enemy(const float time, float width, float height)
{
    this->initVariables(time);
    this->initEnemies(width, height);
}

Enemy::~Enemy()
{

}

const Vector2f Enemy::getGlobalBounds() const
{
    return this->enemy.getSize();;
}

const Vector2f Enemy::getPos()
{
    return this->position;
}

// Functions
void Enemy::spawnEnemy(const VideoMode& vm)
{
    /*
        @return void

        Spawns enemies and sets their color and positions.
        - sets a random position.
        - sets a random color.
        - adds enemy to the vector. 
    */

   this->enemy.setPosition(
       static_cast<float>(rand() % static_cast<int>(vm.width - this->enemy.getSize().x)),
       static_cast<float>(rand() % static_cast<int>(vm.height / 2 - this->enemy.getSize().y))
   );
   
   this->enemy.setTexture(&this->textureSheet);
   this->enemy.setTextureRect(IntRect(64, 0, 64, 192));

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

void Enemy::update(const VideoMode& vm)
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
            this->spawnEnemy(vm);
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

        this->position = this->enemies[i].getPosition();

        //If the enemy is past the bottom of the screen
        if(this->enemies[i].getPosition().y > vm.height)
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