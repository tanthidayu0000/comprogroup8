#include "includeAll.h"
#include "Map1.h"

void Map1::initVariables(float width, float height)
{
	ifstream openfile("Map1.txt");

	this->loadCounter = Vector2i(0, 0);

	if (openfile.is_open())
	{
		string tileLocation;
		openfile >> tileLocation;
		this->tileTexture.loadFromFile(tileLocation);
		this->tiles.setTexture(&this->tileTexture, true);
		this->tiles.setSize(Vector2f(width, height));
		while (!openfile.eof())
		{
			string str;
			openfile >> str;
			char x = str[0], y = str[2];
			if (!isdigit(x) || !isdigit(y))
				this->map[this->loadCounter.x][this->loadCounter.y] = Vector2i(-1, -1);
			else

				this->map[this->loadCounter.x][this->loadCounter.y] = Vector2i(x - '0', y - '0');

			if (openfile.peek() == '\n')
			{
				this->loadCounter.x = 0;
				this->loadCounter.y++;
			}
			else
				this->loadCounter.x++;
		}
		this->loadCounter.y++;
	}
}

void Map1::initPlayers()
{
	this->player = new Player(gui::p2pX(0.f, this->vm), gui::p2pY(88.8f, this->vm), gui::p2pX(2.5f, this->vm), gui::p2pY(4.4f, this->vm));
}

void Map1::initEnemy()
{
	this->enemy = new Enemy();
}

Map1::Map1(float width, float height, const VideoMode& vm)
{
	this->vm = vm;
	this->initVariables(width, height);
	this->initPlayers();
	this->initEnemy();
}

Map1::~Map1()
{
	delete this->player;
	delete this->enemy;
}

void Map1::updateCollision()
{
	if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height > this->ground.y)
	{
		this->player->resetVelocityY();
		this->player->setPosition
		(
			this->player->getGlobalBounds().left,
			this->ground.y - this->player->getGlobalBounds().height
		);
	}
	if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height > this->brickY[0] &&
		this->player->getGlobalBounds().top + this->player->getGlobalBounds().height < this->brickY[0] + gui::p2pY(2.5f, this->vm) &&
		this->player->getGlobalBounds().left + this->player->getGlobalBounds().width > this->brickX[0] &&
		this->player->getGlobalBounds().left + this->player->getGlobalBounds().width > this->brickX[0] + gui::p2pX(2.5f, this->vm)
		)
	{
		this->player->resetVelocityY();
		this->player->setPosition
		(
			this->brickX[0] - this->player->getGlobalBounds().width,
			this->brickY[0] - this->player->getGlobalBounds().height
		);
	}
	if (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width > this->vm.width)
	{
		this->player->resetVelocityX();
		this->player->setPosition
		(
			this->vm.width - this->player->getGlobalBounds().width,
			this->player->getGlobalBounds().top
		);
	}
	if (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width < this->player->getGlobalBounds().width)
	{
		this->player->resetVelocityX();
		this->player->setPosition
		(
			0.f,
			this->player->getGlobalBounds().top
		);
	}
}

void Map1::update()
{
	this->player->update();
	this->enemy->update(this->vm);
	this->updateCollision();
}

void Map1::render(RenderTarget* target, float width, float height)
{
	/*for (auto& i : this->map1)
	{
		target->draw(i);
	}*/
	this->brickX.insert(this->brickX.begin(), 0);
	this->brickY.insert(this->brickY.begin(), 0);
	int k = 0;
	for (int i = 0; i < this->loadCounter.x; i++)
	{
		for (int j = 0; j < this->loadCounter.y; j++)
		{
			if (this->map[i][j].x != -1 && this->map[i][j].y != -1)
			{
				this->tiles.setPosition(i * width, j * height);
				this->tiles.setTextureRect(IntRect(this->map[i][j].x * 48, this->map[i][j].y * 48, 48, 48));
				if (this->tiles.getTextureRect().left == 240 && this->tiles.getTextureRect().top == 0)
				{
					if (this->ground.y != this->tiles.getPosition().y)
					{
						this->ground.y = this->tiles.getPosition().y;
					}
				}
				if (this->tiles.getTextureRect().left == 48 && this->tiles.getTextureRect().top == 48)
				{
					if (this->brickY[k] != this->tiles.getPosition().y)
					{
						this->brickY.push_back(this->tiles.getPosition().y);
						this->brickX.push_back(this->tiles.getPosition().x);
						cout << k << "\n";
						k++;
					}
					/*else if (this->tiles.getPosition().y == this->brickY[k])
					{
						this->brickX.push_back(this->tiles.getPosition().x + gui::p2pX(2.5f, this->vm));
						cout << a << "\n";
						a++;
					}*/
				}
				//this->map1.push_back(tiles);
				target->draw(this->tiles);
			}
		}
	}

	this->player->render(target);
	this->enemy->render(target);
}
