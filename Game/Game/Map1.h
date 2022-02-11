#ifndef MAP1_H
#define MAP1_H

#include "Gui.h"
#include "Player.h"
#include "Enemy.h"

class Map1
{
	private:
		VideoMode vm;
		Texture tileTexture;
		RectangleShape tiles;
		//vector<RectangleShape> map1;

		Vector2i map[100][100];
		Vector2i loadCounter;

		Vector2f ground;
		vector<float> brickX;
		vector<float> brickY;

		Player* player;
		Enemy* enemy;

		void initVariables(float width, float height);
		void initPlayers();
		void initEnemy();

	public:
		Map1(float width, float height, const VideoMode& vm);
		virtual ~Map1();

		void updateCollision();
		void update();
		void render(RenderTarget* target, float width, float height);
};

#endif