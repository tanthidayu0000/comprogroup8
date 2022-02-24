#ifndef MAP1_H
#define MAP1_H

#include "Map.h"
#include "Gui.h"
#include "Player.h"
#include "Box.h"
#include "Coin.h"
#include "heart.h"
#include "Door.h"
#include "puzzle.h"

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
	vector<Heart*> heart;
	Door* door;

	Puzzle* puzzle;

	Text text;
	Font font;
	bool showtext;
	int count;
	float time;

	void initVariables();
	void initPlayers();
	void initBox();
	void initDoor();
	void initheart();
	
public:
	Map1(float width, float height, const VideoMode& vm);
	virtual ~Map1();

	void updateChangeMap();

	bool gameover();

	void updateCoin();
	void updateCollision();
	void update(Vector2f mouseposview, RenderWindow* window);
	void render(RenderTarget* target);
};

#endif