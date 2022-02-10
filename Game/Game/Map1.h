#ifndef MAP1_H
#define MAP1_H

class Map1
{
	private:
		Texture tileTexture;
		Sprite tiles;

		Vector2i map[100][100];
		Vector2i loadCounter;

		void initVariables();

	public:
		Map1();
		virtual ~Map1();

		void update();
		void render(RenderTarget* target);
};

#endif