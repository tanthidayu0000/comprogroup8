#ifndef MAP2_H
#define MAP2_H

#include "Map.h"
#include "Gui.h"
#include "Player.h"
#include "Enemy.h"
#include "Box.h"
#include "Coin.h"

class Map2 :
	public Map
{
private:
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

	Text text;
	Font font;
	bool showtext;
	int count;
	float time;

	void initVariables();
	void initPlayers();
	void initEnemy();
	void initBox();

public:
	Map2(float width, float height, const VideoMode& vm);
	virtual ~Map2();

	void updateChangeMap();

	void updateDeath();

	void updateCoin();
	void updateCollision();
	void update(Vector2f mouseposview);
	void render(RenderTarget* target);

};

#endif