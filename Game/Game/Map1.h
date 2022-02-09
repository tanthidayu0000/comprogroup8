#pragma once
class Map1
{
	private:
		Texture tileTexture;
		Sprite tiles;

		Vector2i map[100][100];
		Vector2i loadCounter;
		RenderWindow *Window;

		void initVariables();
	public:
		Map1();
		virtual ~Map1();
		void update();
		void render();

};

