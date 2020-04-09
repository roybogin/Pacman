#include "Funcs.h"

void init()
{
	window.setKeyRepeatEnabled(false);
	score = 0;
	speedCount = 0;
	player = Player();
	redGhost = RedGhost();
}

void update()
{
	while (speedCount < 100 / SPEED)
	{
		speedCount++;
		return;
	}
	speedCount = 0;
	player.move();
	redGhost.move();
}

void draw()
{
	window.clear();
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			Shape* shape = getShape(row, col);
			window.draw(*shape);
			delete shape;
		}
	}
	window.display();
}

int main()
{

	init();
	
	draw();
	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Down:
					if(player.canChangeDirection(player.DOWN))
						player.setDirection(player.DOWN);
					break;
				case Keyboard::Up:
					if (player.canChangeDirection(player.UP))
						player.setDirection(player.UP);
					break;
				case Keyboard::Left:
					if (player.canChangeDirection(player.LEFT))
						player.setDirection(player.LEFT);
					break;
				case Keyboard::Right:
					if (player.canChangeDirection(player.RIGHT))
						player.setDirection(player.RIGHT);
					break;
				default:
					break;
				}
			}

		}
		update();
		draw();


	}
	return 0;
}
