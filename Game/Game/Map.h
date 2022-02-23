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

	int damage;

public:
	Map(float width, float height, const VideoMode& vm);
	virtual ~Map();

	const bool& getChangeMap() const;

	int getdamage();

	const bool updaterestart();
	void endState();

	virtual int getdamage() = 0;

	virtual void update(Vector2f mouseposview) = 0;
	virtual void render(RenderTarget* target) = 0;
};

#endif