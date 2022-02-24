#include "includeAll.h"
#include "puzzle.h"
#include "AllSprite.h"
#include "Cell.h"

enum gameState { New, Play, Exit };

int Puzzle::puzzle1()
{
    srand(time(0));

    RenderWindow app(VideoMode(256, 256), "15-Puzzle!", Style::None);
    app.setFramerateLimit(60);

    int w = 64;

    gameState state = New;
    AllSprite all;

    while (app.isOpen())
    {
        Event e;
        if (state == New)
        {
            all.Shuffle();
            state = Play;
        }
        if (state == Exit)
        {
            all.Shuffle();
            app.close();
        }
        while (app.pollEvent(e))
        {
            if (e.type == Event::MouseButtonPressed)
            {
                if (e.key.code == Mouse::Left)
                {
                    Vector2i position = Mouse::getPosition(app);
                    int x = position.x / w;
                    int y = position.y / w;
                    int emptyX = all.getEmptyPosition().x;
                    int emptyY = all.getEmptyPosition().y;
                    int dx = emptyX - x;
                    int dy = emptyY - y;

                    if (dx * dy == 0 && abs(dx + dy) == 1)
                    {
                        all.Move(dx, dy);
                    }
                }
            }
            if (all.checkCorrect())
            {
                state = Exit;
            }
        }

        app.clear(Color::White);
        for (int i = 0; i < 15; i++)
        {
            app.draw(all.getSprite(i));
        }

        app.display();

    }
    return 0;
}