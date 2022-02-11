#ifndef MAP1_H
#define MAP1_H

class Map1
{
	private:
		Texture tileTexture;
		RectangleShape tiles;
		//vector<Sprite> map1;

		Vector2i map[100][100];
		Vector2i loadCounter;

		Vector2f collision;

		void initVariables(float width, float height);

	public:
		Map1(float width, float height);
		virtual ~Map1();

		const float getPos() const;

		void update();
		void render(RenderTarget* target, float width, float height);
};

#endif