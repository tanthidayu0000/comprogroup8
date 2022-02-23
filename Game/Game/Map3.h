#ifndef MAP3_H
#define MAP3_H

#include "Map.h"
#include "Gui.h"
#include "Player.h"
#include "Enemy.h"
#include "Box.h"
#include "Coin.h"

class Map3 :
	public Map
{
private:
	Texture bg;
	RectangleShape background;

	Texture tileTexture;
	RectangleShape tiles;

	Vector2i map[100][100];
	Vector2i loadCounter;

	Vector2f ground;
	vector<float> brickX;
	vector<float> brickY;

	Player* player;
	Enemy* enemy;
	Box* box;
	vector<Coin*> coins;

	int count;

	Text text;
	Font font;
	bool showtext;
	float time;

	void initVariables();
	void initPlayers();
	void initEnemy();
	void initBox();

public:
	Map3(float width, float height, const VideoMode& vm);
	virtual ~Map3();

	void updateDeath();

	void updatePlayagain();

	void updateCoin();
	void updateCollision();
	void update(Vector2f mouseposview);
	void render(RenderTarget* target);

};

#endif