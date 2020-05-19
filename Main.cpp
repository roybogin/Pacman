#include "Funcs.h"

void init()
{
	lost = false;
	won = false;
	if (!scoreFont.loadFromFile("score.ttf"))
		throw exception("font file was not found");
	srand(time(NULL));
	window.setKeyRepeatEnabled(false);
	score = 0;

	scoreText.setFont(scoreFont);
	scoreText.setString("SCORE");
	scoreText.setFillColor(Color(255, 255, 255));
	scoreText.setCharacterSize(BLOCK_SIZE);
	scoreText.setPosition(Vector2f(getXForTextInMiddle(scoreText), 0));

	scoreValueText.setFont(scoreFont);
	scoreValueText.setString(std::to_string(score));
	scoreValueText.setFillColor(Color(255, 255, 255));
	scoreValueText.setCharacterSize(BLOCK_SIZE);
	scoreValueText.setPosition(Vector2f(getXForTextInMiddle(scoreValueText), BLOCK_SIZE));

	speedCount = 0;
	ghostsEatenForPellet = 0;
	coinsEaten = 0;
	pelletsEaten = 0;
	lives = 3;
	player = Player();
	redGhost = RedGhost();
	blueGhost = BlueGhost();
	pinkGhost = PinkGhost();
	orangeGhost = OrangeGhost();
	if (MLSolver)
	{
		socketCreate();
		socketConnect();
	}
}

void update()
{
	if (!blueGhost.getCanGetOut() && (coinsEaten >= 30))
		blueGhost.allowGetOut();
	if (!orangeGhost.getCanGetOut() && (float(coinsEaten) / float(NUMBER_OF_COINS) >= 1.0 / 3.0))
		orangeGhost.allowGetOut();

	speedCount++;

	if (speedCount % (int)(SPEED_CONST * SPEED) == 0)
	{
		player.move();
		player.setMouthOpen(!player.getMouthOpen());
	}

	if (speedCount % (int)(SPEED_CONST * SPEED) == 0)
		redGhost.move();
	if (speedCount % (int)(SPEED_CONST * SPEED) == 0)
		blueGhost.move();
	if (speedCount % (int)(SPEED_CONST * SPEED) == 0)
		pinkGhost.move();
	if (speedCount % (int)(SPEED_CONST * SPEED) == 0)
		orangeGhost.move();

	if (speedCount >= SPEED_CONST)
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

	scoreValueText.setString(std::to_string(score));
	scoreValueText.setPosition(Vector2f(getXForTextInMiddle(scoreValueText), BLOCK_SIZE));

	if (won)
	{
		score += 3000;
		exit(0);
	}

	if (lost)
	{
		exit(0);
	}

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
	window.draw(scoreText);
	window.draw(scoreValueText);
	drawLives();
	window.display();
}

int main()
{

	init();
	if (!MLSolver)
	{
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
						if (player.canChangeDirection(player.DOWN))
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
	}
	else  	//Machine learning code	
	{
		int prev_score = 0;
		while (1)
		{
			string done = "false";
			string didWin = "false";
			int reward = 0;
			string recieved = socketRecv();
			string toSend = "";
			if (recieved == "input_num")
				toSend = to_string(ROWS * COLS);
			else if (recieved == "action_num")
				toSend = "4";
			else if (recieved == "input_shape")
				toSend = to_string(ROWS) + "#" + to_string(COLS);
			else if (recieved == "reset")
			{
				lost = false;
				won = false;
				score = 0;
				speedCount = 0;
				ghostsEatenForPellet = 0;
				coinsEaten = 0;
				pelletsEaten = 0;
				player = Player();
				redGhost = RedGhost();
				blueGhost = BlueGhost();
				pinkGhost = PinkGhost();
				orangeGhost = OrangeGhost();
				resetGameMap();
				string observation;
				for (int i = 0; i < ROWS * COLS; i++)
				{
					string text = getMLValue(gameMap[i]);
					observation = observation + text;
					if (i != ROWS * COLS - 1)
						observation = observation + ", ";
				}
				toSend = observation;
			}
			else if (recieved == "close")
			{
				exit(0);
			}
			else if (recieved.substr(0, 4) == "step")
			{
				int action = stoi(recieved.substr(5));
				if(player.canChangeDirection((Player::direction)action))
					player.setDirection((Player::direction)action);
				update();
				reward = score - prev_score - 1;
				if (lost)
				{
					done = "true";
				}
				else
				{
					if (won)
					{
						done = "true";
						didWin = "true";
					}
				}
				
				string observation;
				for (int i = 0; i < ROWS * COLS; i++)
				{
					string text = getMLValue(gameMap[i]);
					observation = observation + text;
					if (i != ROWS * COLS - 1)
						observation = observation + ", ";
				}
				toSend = observation + "#" + to_string(reward) + "#" + done + "#" + didWin;
			}

			socketSend(toSend.c_str());
			prev_score = score;
		}
	}

	return 0;
}
