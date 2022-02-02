#include "Game.h"

//Private functions
void Game::initVariables()
{
    this->window = nullptr;

    //Game logic
    this->points = 0;
    this->enemySpawnTImerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTImerMax;
    this->maxEnemies = 10;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    //this->enemy.setOutlineColor(sf::Color::Green);
    //this->enemy.setOutlineThickness(1.f);
}

//Constructors / Destructors

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
}

//Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

// Functions
void Game::spawnEnemy()
{
    /*
        @return void

        Spawns enemies and sets their color and positions.
        - sets a random position.
        - sets a random color.
        - adds enemy to the vector. 
    */

   this->enemy.setPosition(
       static_cast<float>(rand() % static_cast<int>(this->window.getSize().x - this->enemy.getSize().x)),
       static_cast<float>(rand() % static_cast<int>(this->window.getSize().y - this->enemy.getSize().y))
   );
   
   this->enemy.setFillColor(sf::Color::Green);

    //Spawn the enemy
   this->enemies.push_back(this->enemy);

   

}   

void Game::pollEvent()
{
    //Event polling
    while(this->window->pollEvent(this->ev))
    {
        switch(this->ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape)
                    this->window.close();
                break;
        }
    }
}

void Game::updateMousePositions()
{
    /**
        @return void

        Updates the mouse positions:
        - Mouse position relative to window (Vector2i)
    */

   this->mousePosWindow = sf::Mouse::getPosition(*this->window);
   this->mousePosView = this->window->mapPixelToCoords(this->mousePosView);
}

void Game::updateEnemies()
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
            this->spawnEnemy();
            this->enemySpawnTimer = 0,f;
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
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(this->enemies[i].getGlobalBounds().contains(this->mousePosView))
            {
                deleted = true;

                //Gain Points
                this->points += 10.f;
            }
        }

        //If the enemy is past the bottom of the screen
        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            deleted = true;
        }

        //Final delete
        if(deleted)
            this->enemies.erase(this->.begin() + i);
    }
}


void Game::update()
{
    this->pollEvents();

    this->updateMousePositions();

    this->updateEnemies();
}

    //Update mouse position
    //Relative to the screen
    //std:cout << "Mouse pos: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";
    //Relative to the window
    //std:cout << "Mouse pos: " 
        //<< sf::Mouse::getPosition(*this->window).x << " " 
        //<< sf::Mouse::getPosition(*this->window).y << "\n";
}

void Game::renderEnemies()
{
    //Rendering all the enemies
    for (auto &e : this->enemies)
    {
        this->window->draw(e);
    }
}
void Game::render()
{
    /*
        @return void

        - clear old frame
        - render objects
        - display frame in window
    
        Renders the game objects.
    */
    this->window->clear();

    //Draw game objects
    this->renderEnemies();

    this->window->display();
}