#include "Funcs.h"
Shape* getShape(int row, int col)
{
	switch (getInMap(row, col))
	{
	case gameObject::NOTHING:
	{
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		shape->setFillColor(Color());
		return shape;
	}
	case gameObject::COIN:
	{
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		shape->setFillColor(Color(255, 255, 255));
		return shape;
	}
	case gameObject::PLAYER:
	{
		CircleShape* shape = new CircleShape(BLOCK_SIZE / 2);
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		shape->setFillColor(Color(255, 255, 0));
		return shape;
	}
	case gameObject::WALL:
	{
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		shape->setFillColor(Color(0, 0, 255));
		return shape;
	}
	case gameObject::RED_GHOST:
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		shape->setFillColor(Color(255, 0, 0));
		return shape;
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