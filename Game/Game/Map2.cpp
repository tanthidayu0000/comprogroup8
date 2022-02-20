#include "includeAll.h"
#include "Map2.h"

void Map2::initVariables()
{
	ifstream openfile("Map2.txt");

	this->loadCounter = Vector2i(0, 0);

	if (openfile.is_open())
	{
		string tileLocation;
		openfile >> tileLocation;
		this->tileTexture.loadFromFile(tileLocation);
		this->tiles.setTexture(this->tileTexture);
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

Map2::Map2()
{
	this->initVariables();
}

Map2::~Map2()
{

}

void Map2::update()
{

}

void Map2::render(RenderTarget* target)
{
	for (int i = 0; i < this->loadCounter.x; i++)
	{
		for (int j = 0; j < this->loadCounter.y; j++)
		{
			if (this->map[i][j].x != -1 && this->map[i][j].y != -1)
			{
				this->tiles.setPosition(i * 48, j * 48);
				this->tiles.setTextureRect(IntRect(this->map[i][j].x * 48, this->map[i][j].y * 48, 48, 48));
				target->draw(this->tiles);
			}

		}
	}

}


