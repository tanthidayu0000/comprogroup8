#include "includeAll.h"
#include "Map3.h"

void Map3::initVariables()
{
	this->time = 0.f;
	this->dtime = 0.f;
	this->showtext = false;
	this->count = 0;

	if (!this->font.loadFromFile("Fonts/PatrickHand-Regular.ttf"))
	{
		throw("ERROR::MAP3::CLOUD NOT LOAD FONT");
	}

	this->text.setCharacterSize(80);
	this->text.setFont(this->font);
	this->text.setFillColor(Color::White);
	this->text.setOutlineColor(Color::Black);
	this->text.setOutlineThickness(2);
	this->text.setString("You must pick up all coins and open box.");
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
	this->text.setPosition(this->vm.width / 2, this->vm.height / 2);

	this->bg.loadFromFile("Background/dark.jpg");

	this->background.setSize(
		Vector2f(
			static_cast<float>(this->vm.width),
			static_cast<float>(this->vm.height)
		)
	);
	this->background.setTexture(&this->bg);

	this->brickX.insert(this->brickX.begin(), 0);
	this->brickY.insert(this->brickY.begin(), 0);

	ifstream openfile("Map/Map3.txt");

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

void Map3::initPlayers()
{
	this->player = new Player(this->vm);
}

void Map3::initEnemy()
{
	this->enemy = new Enemy(100.f, gui::p2pX(6.6f, this->vm), gui::p2pY(35.5f, this->vm));
}

void Map3::initBox()
{
	this->box = new Box(gui::p2pX(82.5f, this->vm), gui::p2pY(53.33f, this->vm), this->vm);
}

void Map3::initheart()
{
	for(int i = 0; i < 3; i++)
	{
		this->heart.push_back(new Heart(gui::p2pX(2.5f*(i+1), this->vm), gui::p2pY(4.45f, this->vm), this->vm));

	}
}

Map3::Map3(float width, float height, const VideoMode& vm)
	: Map(width, height, vm)
{
	this->initVariables();
	this->initPlayers();
	this->initEnemy();
	this->initBox();
	this->initheart();
}

Map3::~Map3()
{
	delete this->player;
	delete this->enemy;
	delete this->box;
}

void Map3::updateDeath()
{
	if (this->player->getPos().x + this->player->getGlobalBounds().x > this->enemy->getPos().x + gui::p2pX(1.f, this->vm) &&
		this->player->getPos().x < this->enemy->getPos().x + this->enemy->getGlobalBounds().x - gui::p2pX(1.f, this->vm) &&
		this->player->getPos().y > this->enemy->getPos().y + this->enemy->getGlobalBounds().y / 3 &&
		this->player->getPos().y < this->enemy->getPos().y + this->enemy->getGlobalBounds().y - gui::p2pY(3.5f, this->vm)
		)
	{
		if (this->damage == 3)
		{
			this->player->setPosition
			(
				gui::p2pX(0.f, this->vm),
				gui::p2pY(88.8f, this->vm)
			);
			this->damage = 0;
		}
		else 
		{
			this->damage += 1;
		}
		this->dtime += 1.f;
	}
}

void Map3::updatePlayagain()
{
	if (this->player->getPos().x >= gui::p2pX(97.5f, this->vm) &&
		this->player->getPos().y >= this->ground.y - this->player->getGlobalBounds().y &&
		Keyboard::isKeyPressed(Keyboard::Key::Enter))
	{
		if (this->coins.empty() && this->box->openbox())
		{
			this->endState();
		}
		else
			this->showtext = true;
	}
}

int Map3::getdamage()
{
	return this->damage;
}

void Map3::updateHeart()
{
	if (this->damage > 0 && this->dtime >= 50.f)
	{
		this->heart.pop_back();
		this->dtime = 0.f;
	}
}

void Map3::updateCoin()
{
	for (int i = 1, j = 1; i < this->brickX.size(), j < this->brickY.size(); i += 2, j++)
	{
		if (this->count == 0)
		{
			if (this->brickX[i] == this->box->getPos().x && this->brickY[j] >= this->box->getPos().y) continue;
			this->coins.push_back(new Coin(this->brickX[i], this->brickY[j] - gui::p2pY(4.45f, this->vm), this->vm));
		}
		else break;
	}
	this->count++;

	for (int i = 0; i < this->coins.size(); i++)
	{
		if 
			(
			this->player->getPos().y + this->player->getGlobalBounds().y / 2 >= this->coins[i]->getPos().y &&
			this->player->getPos().y + this->player->getGlobalBounds().y / 2 <= this->coins[i]->getPos().y + gui::p2pY(4.45f, this->vm) &&
			this->player->getPos().x + this->player->getGlobalBounds().x / 2 >= this->coins[i]->getPos().x &&
			this->player->getPos().x + this->player->getGlobalBounds().x / 2 <= this->coins[i]->getPos().x + gui::p2pX(2.5f, this->vm)
			)
		{
			this->coins.erase(this->coins.begin()+i);
		}
	}

}

void Map3::updateCollision()
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

void Map3::update(Vector2f mouseposview)
{
	this->updatePlayagain();
	this->player->update(this->vm);
	this->enemy->update(this->vm);
	this->updateCollision();
	this->updateCoin();
	this->updateHeart();

	for (int i = 0; i < this->coins.size(); i++)
	{
		this->coins[i]->update();
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::Enter) &&
		this->player->getPos().y + this->player->getGlobalBounds().y / 2 >= this->box->getPos().y &&
		this->player->getPos().y + this->player->getGlobalBounds().y / 2 <= this->box->getPos().y + gui::p2pY(4.45f, this->vm) &&
		this->player->getPos().x + this->player->getGlobalBounds().x / 2 >= this->box->getPos().x &&
		this->player->getPos().x + this->player->getGlobalBounds().x / 2 <= this->box->getPos().x + gui::p2pX(2.5f, this->vm)
		)
	{
		this->box->update();
	}

	this->updateDeath();
}

void Map3::render(RenderTarget* target)
{
	target->draw(this->background);

	int g = 0;
	int k = 0, a = 0;
	float check1 = 0, count = 2, check2 = 0, check3 = 0;
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
				if (this->tiles.getTextureRect().left == 0 && this->tiles.getTextureRect().top == 0)
				{
					if (g == 0)
					{
						this->ground.y = this->tiles.getPosition().y;
						g++;
					}
				}
				else if ((this->tiles.getTextureRect().left == 48 && this->tiles.getTextureRect().top == 0) ||
						(this->tiles.getTextureRect().left == 192 && this->tiles.getTextureRect().top == 0))
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

							if (check1 == this->tiles.getPosition().y && check2 == 1)
							{
								this->brickY.push_back(this->tiles.getPosition().y);
								//cout << k << " " << this->brickY[k] << " " << a << " " << this->brickX[a] << "\n";
								k++;
							}
							//cout << k << " " << this->brickY[k] << " " << a << " " << this->brickX[a] << "\n";
							a++;
						}
					}
				}

				target->draw(this->tiles);

			}
			else
			{
				check2 = 0;
				if(count == 0 && check3 == 0)
				{
					this->brickX.push_back(this->brickX[a]);
					//cout << k << " " << this->brickY[k] << " " << a << " " << this->brickX[a] << "\n";
					a++;
					check3++;
				}
			}
		}
	}

	for (int i = 0; i < this->coins.size(); i++)
	{
		this->coins[i]->render(target);
	}

	this->box->render(target);
	this->player->render(target);
	this->enemy->render(target);
	if (this->showtext)
	{
		target->draw(this->text);
		this->time += 1.f;
		if (this->time >= 100.f)
		{
			this->showtext = false;
			this->time = 0.f;
		}
	}
	for (int i = 0; i < this->heart.size(); i++)
	{
		this->heart[i]->render(target);
	}	
}


