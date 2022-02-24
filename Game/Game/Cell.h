#pragma once
class Cell
{
private:
    int Number;
    Vector2i Position;
    Sprite sprite;
    const int w = 64;

public:
    Cell(int number, Sprite sprite);
    int GetNumber();
    void Move(int dx, int dy);
    Vector2i GetPosition();
    Sprite getSprite();
};

