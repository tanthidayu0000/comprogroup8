#ifndef MAP1_H
#define MAP1_H

class Map1
{
	private:
		Texture tileTexture;
		Sprite tiles;
		vector<Sprite> map1;

		Vector2i map[100][100];
		Vector2i loadCounter;

		Vector2f collision;

		void initVariables();

	public:
		Map1();
		virtual ~Map1();

		const float getPos() const;

		void update();
		void render(RenderTarget* target);
};

#endif