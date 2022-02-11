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

Map1::Map1(float width, float height)
{
	this->initVariables(width, height);
}

Map1::~Map1()
{
	
}

const float Map1::getPos() const
{
	return this->collision.y;
}

void Map1::update()
{
	
}

void Map1::render(RenderTarget* target, float width, float height)
{
	/*for (auto& i : this->map1)
	{
		target->draw(i);
	}*/
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
					this->collision.y = this->tiles.getPosition().y;
				}
				//this->map1.push_back(tiles);
				target->draw(this->tiles);
			}
		}
	}
}
