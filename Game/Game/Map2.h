#pragma once
class Map2
{
private:
	Texture tileTexture;
	Sprite tiles;

	Vector2i map[100][100];
	Vector2i loadCounter;
	RenderWindow* Window;

	void initVariables();
public:
	Map2();
	virtual ~Map2();
	void update();
	void render();

};

