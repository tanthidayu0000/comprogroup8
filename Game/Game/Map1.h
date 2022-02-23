#ifndef MAP1_H
#define MAP1_H

#include "Map.h"
#include "Gui.h"
#include "Player.h"
#include "Box.h"
#include "Coin.h"

class Map1 :
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
	Box* box;
	vector<Coin*> coins;

	Text text;
	Font font;
	bool showtext;
	int count;

	void initVariables();
	void initPlayers();
	void initBox();

public:
	Map1(float width, float height, const VideoMode& vm);
	virtual ~Map1();

	void updateChangeMap();

	void updateCoin();
	void updateCollision();
	void update(Vector2f mouseposview);
	void render(RenderTarget* target);
};

#endif