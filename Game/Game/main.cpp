#include "includeAll.h"

using namespace std;

int main()
{
	srand(static_cast<unsigned>(time(0)));

	RenderWindow window(VideoMode(800, 600), "GAME 2D");
	

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
			window.clear(Color::White);
			window.display();
	}

	return 0;
}