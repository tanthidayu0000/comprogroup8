#include "includeAll.h"
#include "Map1.h"

void Map1::initVariables()
{
	this->background.setSize(
		Vector2f(
			static_cast<float>(this->vm.width),
			static_cast<float>(this->vm.height)
		)
	);
	this->background.setFillColor(Color::Black);

	this->brickX.insert(this->brickX.begin(), 0);
	this->brickY.insert(this->brickY.begin(), 0);

	ifstream openfile("Map/Map1.txt");

	this->loadCounter = Vector2i(0, 0);

	if (openfile.is_open())
	{
		string tileLocation;
		openfile >> tileLocation;
		this->tileTexture.loadFromFile(tileLocation);
		this->tiles.setTexture(&this->tileTexture, true);
		this->tiles.setSize(Vector2f(this->width, this->height));
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
	this->player = new Player(gui::p2pX(0.f, this->vm), gui::p2pY(88.8f, this->vm), gui::p2pX(2.5f, this->vm), gui::p2pY(4.45f, this->vm));
}

Map1::Map1(float width, float height, const VideoMode& vm)
	: Map(width, height, vm)
{
	this->initVariables();
	this->initPlayers();
}

Map1::~Map1()
{
	delete this->player;
}

void Map1::updateChangeMap()
{
	if (this->player->getPos().x >= gui::p2pX(97.5f, this->vm) &&
		this->player->getPos().y >= this->ground.y - this->player->getGlobalBounds().y &&
		Keyboard::isKeyPressed(Keyboard::Key::Enter))
	{
		this->endState();
	}
}

void Map1::updateCollision()
{
	for (int i = 1, j = 1; i < this->brickX.size(), j < this->brickY.size(); i += 2, j++)
	{
		if (this->player->getPos().y + this->player->getGlobalBounds().y > this->brickY[j] &&
			this->player->getPos().y + this->player->getGlobalBounds().y < this->brickY[j] + gui::p2pY(4.45f, this->vm) &&
			this->player->getPos().x + this->player->getGlobalBounds().x > this->brickX[i] + gui::p2pX(1.f, this->vm) &&
			this->player->getPos().x + this->player->getGlobalBounds().x < this->brickX[i + 1] + gui::p2pX(2.5f, this->vm) + this->player->getGlobalBounds().x / 2
			)
		{
			this->player->resetVelocityY();
			this->player->setPosition
			(
				this->player->getPos().x,
				this->brickY[j] - this->player->getGlobalBounds().y
			);
		}

		if (this->player->getPos().y == this->brickY[j] + gui::p2pY(4.45f, this->vm) &&
			this->player->getPos().x + this->player->getGlobalBounds().x > this->brickX[i] + gui::p2pX(1.f, this->vm) &&
			this->player->getPos().x + this->player->getGlobalBounds().x < this->brickX[i + 1] + gui::p2pX(2.5f, this->vm) + this->player->getGlobalBounds().x / 2
			)
		{
			this->player->resetVelocityY();
			this->player->setPosition
			(
				this->player->getPos().x,
				this->ground.y - this->player->getGlobalBounds().y
			);
		}
	}

	if (this->player->getPos().y + this->player->getGlobalBounds().y > this->ground.y)
	{
		this->player->resetVelocityY();
		this->player->setPosition
		(
			this->player->getPos().x,
			this->ground.y - this->player->getGlobalBounds().y
		);
	}
	if (this->player->getPos().x + this->player->getGlobalBounds().x > this->vm.width)
	{
		this->player->resetVelocityX();
		this->player->setPosition
		(
			this->vm.width - this->player->getGlobalBounds().x,
			this->player->getPos().y
		);
	}
	if (this->player->getPos().x + this->player->getGlobalBounds().x < this->player->getGlobalBounds().x)
	{
		this->player->resetVelocityX();
		this->player->setPosition
		(
			0.f,
			this->player->getPos().y
		);
	}
}

void Map1::update()
{
	this->player->update();
	this->updateCollision();

	this->updateChangeMap();
}

void Map1::render(RenderTarget* target)
{
	target->draw(this->background);

	int k = 0, a = 0;
	float check1 = 0, count = 2, check2 = 0;
	for (int j = 0; j < this->loadCounter.y; j++)
	{
		for (int i = 0; i < this->loadCounter.x; i++)
		{
			if (this->map[i][j].x != -1 && this->map[i][j].y != -1)
			{
				if (i * width > gui::p2pX(100.f, this->vm)) continue;
				check2++;
				this->tiles.setPosition(i * this->width, j * this->height);
				this->tiles.setTextureRect(IntRect(this->map[i][j].x * 48, this->map[i][j].y * 48, 48, 48));
				if (this->tiles.getTextureRect().left == 240 && this->tiles.getTextureRect().top == 0)
				{
					if (this->ground.y != this->tiles.getPosition().y)
					{
						this->ground.y = this->tiles.getPosition().y;
					}
				}
				else if (this->tiles.getTextureRect().left == 48 && this->tiles.getTextureRect().top == 48)
				{
					if (this->brickY[k] != this->tiles.getPosition().y)
					{
						if (count == 0)
						{
							this->brickX.push_back(this->brickX[a]);
							//cout << k << " " << this->brickY[k] << " " << a << " " << this->brickX[a] << "\n";
							a++;
						}
						check1 = this->tiles.getPosition().y;
						this->brickY.push_back(this->tiles.getPosition().y);
						this->brickX.push_back(this->tiles.getPosition().x);
						//cout << k << " " << this->brickY[k] << " " << a << " " << this->brickX[a] << "\n";
						k++;
						a++;
						count = 0;
					}
					else
					{
						if (k != 0)
						{
							count++;
							if (count > 1 && check2 > 2)
							{
								this->brickX.pop_back();
								a--;
							}
							
							this->brickX.push_back(this->tiles.getPosition().x);
							a++;

							if (check1 == this->tiles.getPosition().y && check2 == 1)
							{
								this->brickY.push_back(this->tiles.getPosition().y);
								//cout << k << " " << this->brickY[k] << " " << a << " " << this->brickX[a] << "\n";
								k++;
							}
							//cout << k << " " << this->brickY[k] << " " << a << " " << this->brickX[a] << "\n";
						}
					}
				}

				target->draw(this->tiles);

			}
			else
			{
				check2 = 0;
			}
		}
	}

	this->player->render(target);
}
