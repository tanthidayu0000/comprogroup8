#ifndef MAP3_H
#define MAP3_H

class Map3
{
private:
	Texture tileTexture;
	Sprite tiles;

	Vector2i map[100][100];
	Vector2i loadCounter;

	void initVariables();

public:
	Map3();
	virtual ~Map3();

	void update();
	void render(RenderTarget* target);
};

#endif