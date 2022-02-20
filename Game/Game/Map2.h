#ifndef MAP2_H
#define MAP2_H

class Map2
{
private:
	Texture tileTexture;
	Sprite tiles;

	Vector2i map[100][100];
	Vector2i loadCounter;

	void initVariables();

public:
	Map2();
	virtual ~Map2();

	void update();
	void render(RenderTarget* target);
};

#endif