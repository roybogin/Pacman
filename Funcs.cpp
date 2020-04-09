#include "Funcs.h"
vector<Shape*> getShape(int row, int col)
{

	switch (getInMap(row, col))
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
		shape2->setFillColor(Color(255, 255, 255));
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
		return vec;
	}
	case gameObject::WALL:
	{
		vector<Shape*> vec;
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		shape->setFillColor(Color(0, 0, 255));
		vec.push_back(shape);
		return vec;
	}
	case gameObject::RED_GHOST:
	{
		vector<Shape*> vec;
		RectangleShape* shape = new RectangleShape(Vector2f(BLOCK_SIZE, BLOCK_SIZE));
		shape->setPosition(Vector2f(col * BLOCK_SIZE, row * BLOCK_SIZE));
		shape->setFillColor(Color(255, 0, 0));
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