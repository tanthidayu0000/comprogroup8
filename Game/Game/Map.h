#ifndef MAP_H
#define MAP_H

class Map
{
protected:
	stack<Map*>* maps;

	VideoMode vm;

	float width;
	float height;

	bool restart;
	bool changeMap;


	int numheart;
	int damage;

	bool checkPuz;

public:
	Map(float width, float height, const VideoMode& vm);
	virtual ~Map();

	const bool& getChangeMap() const;

	const bool updaterestart();
	void endState();

	virtual void update(Vector2f mouseposview, RenderWindow* window) = 0;
	virtual void render(RenderTarget* target) = 0;
};

#endif