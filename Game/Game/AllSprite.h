#pragma once
#include "Cell.h"

class AllSprite
{
private:
    vector<Vector2i> correct;
    vector <Cell> cells;
    Vector2i emptyPos;
    Texture t;
    Sprite spriteTiles;
    const int w = 64;

public:
    AllSprite();
    void Shuffle();
    int GetNumber(int Xpos, int Ypos);
    Sprite getSprite(int cell);
    void Move(int dx, int dy);
    Vector2i getEmptyPosition();
    bool checkCorrect();
};

