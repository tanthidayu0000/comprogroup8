#ifndef MAP_H
#define MAP_H

class Map
{
protected:
	stack<Map*>* maps;

	VideoMode vm;

	float width;
	float height;

	bool changeMap;

public:
	Map(float width, float height, const VideoMode& vm);
	virtual ~Map();

	const bool& getChangeMap() const;

	void endState();

	virtual void update() = 0;
	virtual void render(RenderTarget* target) = 0;
};

#endif