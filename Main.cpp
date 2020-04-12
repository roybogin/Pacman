#include "Funcs.h"

void init()
{
	srand(time(NULL));
	window.setKeyRepeatEnabled(false);
	score = 0;
	speedCount = 0;
	ghostsEatenForPellet = 0;
	coinsEaten = 0;
	player = Player();
	redGhost = RedGhost();
	blueGhost = BlueGhost();
	pinkGhost = PinkGhost();
	orangeGhost = OrangeGhost();
}

void update()
{
	if (!blueGhost.getCanGetOut() && (coinsEaten < 30))
		blueGhost.allowGetOut();
	if (!orangeGhost.getCanGetOut() && (float(coinsEaten) / float(NUMBER_OF_COINS) < 1.0 / 3.0))
		orangeGhost.allowGetOut();

	speedCount++;
	if (speedCount % (100 / PLAYER_SPEED) == 0)
		player.move();

	if (speedCount % (100 / GHOST_SPEED) == 0)
		redGhost.move();
	if (speedCount % (100 / GHOST_SPEED) == 0)
		blueGhost.move();
	if (speedCount % (100 / GHOST_SPEED) == 0)
		pinkGhost.move();
	if (speedCount % (100 / GHOST_SPEED) == 0)
		orangeGhost.move();

	if ((speedCount % (100 / PLAYER_SPEED) == 0) && (speedCount % (100 / GHOST_SPEED) == 0))
		speedCount = 0;

	if (redGhost.getPelletTime() > 0)
	{
		redGhost.setPelletTime(redGhost.getPelletTime() - 1);
	}
	if (blueGhost.getPelletTime() > 0)
	{
		blueGhost.setPelletTime(blueGhost.getPelletTime() - 1);
	}
	if (pinkGhost.getPelletTime() > 0)
	{
		pinkGhost.setPelletTime(pinkGhost.getPelletTime() - 1);
	}
	if (orangeGhost.getPelletTime() > 0)
	{
		orangeGhost.setPelletTime(orangeGhost.getPelletTime() - 1);
	}

	setGameMap(orangeGhost.getLocation().first, orangeGhost.getLocation().second, ORANGE_GHOST);
	setGameMap(pinkGhost.getLocation().first, pinkGhost.getLocation().second, PINK_GHOST);
	setGameMap(blueGhost.getLocation().first, blueGhost.getLocation().second, BLUE_GHOST);
	setGameMap(redGhost.getLocation().first, redGhost.getLocation().second, RED_GHOST);

	setGameMap(player.getLocation().first, player.getLocation().second, PLAYER);

}

void draw()
{
	window.clear();
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			vector<Shape*> shapes = getShapes(row, col);
			for (Shape* shape : shapes)
			{
				window.draw(*shape);
				delete shape;
			}
		}
	}
	window.display();	//TODO: add lives and score
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
