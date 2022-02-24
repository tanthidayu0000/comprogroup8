#include "includeAll.h"
#include "AllSprite.h"

AllSprite::AllSprite()
{
    this->emptyPos.x = 3;
    this->emptyPos.y = 3;

    for (int num = 1; num < 16; num++)
    {
        int x = (num - 1) % 4;
        int y = (num - 1) / 4;
        this->t.loadFromFile("puzzle/15.png");
        this->spriteTiles.setTexture(this->t);
        this->spriteTiles.setTextureRect(IntRect(x * w, y * w, w, w));
        this->cells.push_back(Cell(num, spriteTiles));
        this->correct.push_back(Vector2i(x, y));
    }
}

int AllSprite::GetNumber(int x, int y)
{
    Vector2i pos;
    for (int i = 0; i < this->cells.size(); i++)
    {
        pos = this->cells[i].GetPosition();
        if (pos.x == x && pos.y == y)
            return this->cells[i].GetNumber();
    }
}

void AllSprite::Move(int dx, int dy)
{
    if (dx == -1 && this->emptyPos.x == 3) return;
    if (dx == 1 && this->emptyPos.x == 0) return;
    if (dy == -1 && this->emptyPos.y == 3) return;
    if (dy == 1 && this->emptyPos.y == 0) return;

    int x = this->emptyPos.x - dx;
    int y = this->emptyPos.y - dy;
    this->emptyPos.x = x;
    this->emptyPos.y = y;

    Vector2i pos;
    for (int i = 0; i < this->cells.size(); i++)
    {
        pos = this->cells[i].GetPosition();
        if (pos.x == x && pos.y == y)
        {
            this->cells[i].Move(dx, dy);
        }
    }

}

void AllSprite::Shuffle()
{
    srand(time(0));
    int choise;
    for (int i = 0; i < 200; i++)
    {
        choise = rand() % 4;
        switch (choise)
        {
        case 0: Move(-1, 0); break;
        case 1: Move(1, 0); break;
        case 2: Move(0, -1); break;
        case 3: Move(0, 1); break;
        }
    }
}

Sprite AllSprite::getSprite(int cell)
{
    return this->cells[cell].getSprite();
}

Vector2i AllSprite::getEmptyPosition()
{
    return this->emptyPos;
}

bool AllSprite::checkCorrect()
{
    int count = 0;
    for (int i = 0; i < this->correct.size(); i++)
    {
        if (this->correct[i] == this->cells[i].GetPosition())
            count++;
    }
    if (count == 15)
        return true;
    else
        return false;
}
