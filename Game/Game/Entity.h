#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
private:


protected:
	RectangleShape shape;
	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	virtual void move(const float& dt, const float dir_x, const float dir_y);

	virtual void update(const float& dt);
	virtual void render(RenderTarget* target);

};

#endif