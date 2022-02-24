#include "includeAll.h"
#include "Cell.h"

Cell::Cell(int number, Sprite sprite)
{
    this->Number = number;
    this->Position.x = (number - 1) % 4;
    this->Position.y = (number - 1) / 4;
    this->sprite = sprite;
    this->sprite.setPosition(Vector2f(Position.x * w, Position.y * w));
}

int Cell::GetNumber()
{
    return this->Number;
}

Vector2i Cell::GetPosition()
{
    return this->Position;
}

void Cell::Move(int dx, int dy)
{
    this->Position.y += dy;
    this->Position.x += dx;

    Vector2f temp = this->sprite.getPosition();
    temp.x += dx * w;
    temp.y += dy * w;
    this->sprite.setPosition(Vector2f(temp));
}

Sprite Cell::getSprite()
{
    return this->sprite;
}