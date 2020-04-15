#include "Funcs.h"
vector<Shape*> getShapes(int row, int col)
{
	gameObject obj = getInMap(row, col);
	row += STARTING_ROWS;
	switch (obj)
	{
	case gameObject::NOTHING:
	{
		vector<Shape*> vec;
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		shape->setFillColor(Color());
		vec.push_back(shape);
		return vec;
	}
	case gameObject::COIN:
	{
		vector<Shape*> vec;

		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		shape->setFillColor(Color());
		vec.push_back(shape);

		RectangleShape* shape2 = new RectangleShape(Vector2f(BLOCK_SIZE/9.0, BLOCK_SIZE/9.0));
		shape2->setPosition(Vector2f((col + 1.0/3) * BLOCK_SIZE, (row + 1.0/3) * BLOCK_SIZE));
		shape2->setFillColor(Color(255, 184, 151));
		vec.push_back(shape2);
		return vec;
	}
	case gameObject::PLAYER:
	{
		vector<Shape*> vec;
		CircleShape* shape = new CircleShape(BLOCK_SIZE / 2);
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		shape->setFillColor(Color(255, 255, 0));
		vec.push_back(shape);
		if (player.getMouthOpen())
		{
			CircleShape* mouth = new CircleShape(BLOCK_SIZE / 3.0, 3);
			mouth->setOrigin(BLOCK_SIZE / 3.0, BLOCK_SIZE / 3.0);
			mouth->setFillColor(Color());
			switch (player.getDirection())
			{
			case Player::UP:
				mouth->setRotation(180);
				mouth->setPosition(Vector2f((col + 1.0 / 2) * BLOCK_SIZE, (row + 1.0 / 6) * BLOCK_SIZE));
				break;
			case Player::DOWN:
				mouth->setPosition(Vector2f((col + 1.0 / 2) * BLOCK_SIZE, (row + 5.0 / 6) * BLOCK_SIZE));
				break;
			case Player::LEFT:
				mouth->setRotation(-30);
				mouth->setPosition(Vector2f((col + 1.0 / 6) * BLOCK_SIZE, (row + 1.0 / 2) * BLOCK_SIZE));
				break;
			case Player::RIGHT:
				mouth->setRotation(30);
				mouth->setPosition(Vector2f((col + 5.0 / 6) * BLOCK_SIZE, (row + 1.0 / 2) * BLOCK_SIZE));
				break;
			}
			vec.push_back(mouth);
		}
		return vec;
	}
	case gameObject::WALL:
	{
		vector<Shape*> vec;
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		shape->setFillColor(Color(33, 33, 222));
		vec.push_back(shape);
		return vec;
	}
	case gameObject::RED_GHOST:
	{
		vector<Shape*> vec;
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		if (!redGhost.getIsDead())
		{
			if (redGhost.getPelletTime() == 0)	//not in pellet time
				shape->setFillColor(Color(255, 0, 0));
			else if (redGhost.getPelletTime() <= PELLET_BLINK && redGhost.getPelletTime() % 10 < 5)
				shape->setFillColor(Color(255, 255, 255));
			else
				shape->setFillColor(Color(0, 0, 255));
		}
		else
			shape->setFillColor(Color(0, 0, 0));
		vec.push_back(shape);

		CircleShape* eye1 = new CircleShape(BLOCK_SIZE / 4);
		eye1->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		eye1->setFillColor(Color(255, 255, 255));
		vec.push_back(eye1);

		CircleShape* eye2 = new CircleShape(BLOCK_SIZE / 4);
		eye2->setPosition(Vector2f((col + 0.5) * BLOCK_SIZE, row * BLOCK_SIZE));
		eye2->setFillColor(Color(255, 255, 255));
		vec.push_back(eye2);

		return vec;
	}
	case gameObject::BLUE_GHOST:
	{
		vector<Shape*> vec;
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		if (!blueGhost.getIsDead())
		{
			if (blueGhost.getPelletTime() == 0)
				shape->setFillColor(Color(0, 255, 255));
			else if (blueGhost.getPelletTime() <= PELLET_BLINK && blueGhost.getPelletTime() % 10 < 5)
				shape->setFillColor(Color(255, 255, 255));
			else
				shape->setFillColor(Color(0, 0, 255));
		}
		else
			shape->setFillColor(Color(0, 0, 0));
		vec.push_back(shape);

		CircleShape* eye1 = new CircleShape(BLOCK_SIZE / 4);
		eye1->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		eye1->setFillColor(Color(255, 255, 255));
		vec.push_back(eye1);

		CircleShape* eye2 = new CircleShape(BLOCK_SIZE / 4);
		eye2->setPosition(Vector2f((col + 0.5) * BLOCK_SIZE, row * BLOCK_SIZE));
		eye2->setFillColor(Color(255, 255, 255));
		vec.push_back(eye2);

		return vec;
	}
	case gameObject::PINK_GHOST:
	{
		vector<Shape*> vec;
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		if (!pinkGhost.getIsDead())
		{
			if (pinkGhost.getPelletTime() == 0)
				shape->setFillColor(Color(255, 184, 255));
			else if (pinkGhost.getPelletTime() <= PELLET_BLINK && pinkGhost.getPelletTime() % 10 < 5)
				shape->setFillColor(Color(255, 255, 255));
			else
				shape->setFillColor(Color(0, 0, 255));
		}
		else
			shape->setFillColor(Color(0, 0, 0));
		vec.push_back(shape);

		CircleShape* eye1 = new CircleShape(BLOCK_SIZE / 4);
		eye1->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		eye1->setFillColor(Color(255, 255, 255));
		vec.push_back(eye1);

		CircleShape* eye2 = new CircleShape(BLOCK_SIZE / 4);
		eye2->setPosition(Vector2f((col + 0.5) * BLOCK_SIZE, row * BLOCK_SIZE));
		eye2->setFillColor(Color(255, 255, 255));
		vec.push_back(eye2);

		return vec;
	}
	case gameObject::ORANGE_GHOST:
	{
		vector<Shape*> vec;
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		if (!orangeGhost.getIsDead())
		{
			if (orangeGhost.getPelletTime() == 0)
				shape->setFillColor(Color(255, 184, 82));
			else if (orangeGhost.getPelletTime() <= PELLET_BLINK && orangeGhost.getPelletTime() % 10 < 5)
				shape->setFillColor(Color(255, 255, 255));
			else
				shape->setFillColor(Color(0, 0, 255));
		}
		else
			shape->setFillColor(Color(0, 0, 0));
		vec.push_back(shape);

		CircleShape* eye1 = new CircleShape(BLOCK_SIZE / 4);
		eye1->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		eye1->setFillColor(Color(255, 255, 255));
		vec.push_back(eye1);

		CircleShape* eye2 = new CircleShape(BLOCK_SIZE / 4);
		eye2->setPosition(Vector2f((col + 0.5) * BLOCK_SIZE, row * BLOCK_SIZE));
		eye2->setFillColor(Color(255, 255, 255));
		vec.push_back(eye2);

		return vec;
	}
	case gameObject::POWER_PELLET:
	{
		vector<Shape*> vec;
		CircleShape* shape = new CircleShape(BLOCK_SIZE / 2);
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		shape->setFillColor(Color(255, 184, 151));
		vec.push_back(shape);
		return vec;
	}
	case gameObject::ONE_WAY_DOOR:
	{
		vector<Shape*> vec;
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE/2));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, (row + 0.25) * BLOCK_SIZE));
		shape->setFillColor(Color(255, 184, 222));
		vec.push_back(shape);
		return vec;
	}
	}
}

gameObject getInMap(int row, int col)
{
	if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
		throw exception("index out of bounds");
	return static_cast<gameObject>(gameMap[row * COLS + col]);
}

void setGameMap(int row, int col, gameObject object)
{
	if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
		throw exception("index out of bounds");
	gameMap[row * COLS + col] = object;
}

void loseLife()
{
	lives--;
	if (lives == 0)
	{
		if(!won)
			lost = true;
		return;
	}

	setGameMap(player.getLocation().first, player.getLocation().second, NOTHING);
	setGameMap(redGhost.getLocation().first, redGhost.getLocation().second, redGhost.getOnSquare());
	setGameMap(blueGhost.getLocation().first, blueGhost.getLocation().second, blueGhost.getOnSquare());
	setGameMap(pinkGhost.getLocation().first, pinkGhost.getLocation().second, pinkGhost.getOnSquare());
	setGameMap(orangeGhost.getLocation().first, orangeGhost.getLocation().second, orangeGhost.getOnSquare());

	player = Player();
	redGhost = RedGhost();
	blueGhost = BlueGhost();
	pinkGhost = PinkGhost();
	orangeGhost = OrangeGhost();
}

float getXForTextInMiddle(Text text)
{
	float HalfTextLength = text.getGlobalBounds().width / 2.0;
	float windowMiddle = COLS * BLOCK_SIZE / 2.0;
	return windowMiddle - HalfTextLength;
}

void drawLives()
{
	int blockX = 2;
	float blockY = STARTING_ROWS + ROWS;
	for (int i = 0; i < lives; i++)
	{
		CircleShape life = CircleShape(BLOCK_SIZE);
		life.setPosition(Vector2f((blockX + 3*i) * BLOCK_SIZE, blockY * BLOCK_SIZE));
		life.setFillColor(Color(255, 255, 0));
		window.draw(life);
		CircleShape mouth = CircleShape(2 * BLOCK_SIZE / 3.0, 3);
		mouth.setOrigin(2 * BLOCK_SIZE / 3.0, 2 * BLOCK_SIZE / 3.0);
		mouth.setRotation(30);
		mouth.setFillColor(Color());
		mouth.setPosition(Vector2f((blockX + 3 * i + 5.0 / 3) * BLOCK_SIZE, (blockY + 1) * BLOCK_SIZE));
		window.draw(mouth);
	}
}

bool coinOrPelletInGame()
{
	if (redGhost.getOnSquare() == COIN || redGhost.getOnSquare() == POWER_PELLET)
		return true;
	if (blueGhost.getOnSquare() == COIN || blueGhost.getOnSquare() == POWER_PELLET)
		return true;
	if (pinkGhost.getOnSquare() == COIN || pinkGhost.getOnSquare() == POWER_PELLET)
		return true;
	if (orangeGhost.getOnSquare() == COIN || orangeGhost.getOnSquare() == POWER_PELLET)
		return true;
	for (int i : gameMap)
	{
		if (i == COIN || i == POWER_PELLET)
			return true;
	}
	return false;
}