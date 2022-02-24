#ifndef MAP_H
#define MAP_H

class Map
{
protected:
	stack<Map*>* maps;

	VideoMode vm;

	float width;
	float height;

	RectangleShape bgPuzzle;

	bool restart;
	bool changeMap;

	int damage;

	bool checkPuz;

public:
	Map(float width, float height, const VideoMode& vm);
	virtual ~Map();

	void renderBGpuzzle(RenderTarget* target);

	const bool& getChangeMap() const;

	const bool updaterestart();
	void endState();

	virtual void update(Vector2f mouseposview, RenderWindow* window) = 0;
	virtual void render(RenderTarget* target) = 0;
};

#endif