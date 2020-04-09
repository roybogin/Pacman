#include "Ghost.h"
#include "Data.h"
#include "Funcs.h"


bool Ghost::canChangeDirection(Ghost::direction d)
{
	if (d == dir)
		return true;
	switch (d)
	{
	case Ghost::UP:
		if (d == DOWN)
			return false;
		break;
	case Ghost::DOWN:
		if (d == UP)
			return false;
		break;
	case Ghost::LEFT:
		if (d == RIGHT)
			return false;
		break;
	case Ghost::RIGHT:
		if (d == LEFT)
			return false;
		break;
	default:
		break;
	}
	int row = location.first;
	int col = location.second;
	int nextRow = row;
	int nextCol = col;
	switch (d)
	{
	case Ghost::UP:
		nextRow = row - 1;
		break;
	case Ghost::DOWN:
		nextRow = row + 1;
		break;
	case Ghost::LEFT:
		nextCol = col - 1;
		break;
	case Ghost::RIGHT:
		nextCol = col + 1;
		break;
	default:
		break;
	}
	return getInMap(nextRow, nextCol) != gameObject::WALL;
}

void Ghost::chooseDirection()
{
	pair<int, int> nextLoc = location;
	double dist;
	direction minDir = dir;
	double minLen = INT_MAX;

	//UP
	if (canChangeDirection(UP))
	{
		nextLoc = pair<int, int>(location.first - 1, location.second);
		dist = sqrt(pow(nextLoc.first - target.first, 2) + pow(nextLoc.second - target.second, 2));
		if (dist <= minLen)
		{
			minLen = dist;
			minDir = UP;
		}
	}

	if (canChangeDirection(LEFT))
	{
		nextLoc = pair<int, int>(location.first, location.second - 1);
		dist = sqrt(pow(nextLoc.first - target.first, 2) + pow(nextLoc.second - target.second, 2));
		if (dist < minLen)
		{
			minLen = dist;
			minDir = LEFT;
		}
	}

	if (canChangeDirection(DOWN))
	{
		nextLoc = pair<int, int>(location.first + 1, location.second);
		dist = sqrt(pow(nextLoc.first - target.first, 2) + pow(nextLoc.second - target.second, 2));
		if (dist < minLen)
		{
			minLen = dist;
			minDir = DOWN;
		}
	}

	dir = minDir;

}



///////////////////////RED///////////////////////

RedGhost::RedGhost()
{
	location = pair<int, int>(1, 10);
	dir = LEFT;
	onSquare = gameObject::NOTHING;
}

void RedGhost::setTarget()
{
	std::pair<int, int> playerLocation = player.getLocation();
	target = playerLocation;
}


void RedGhost::move()
{
	this->chooseDirection();
	int row = location.first;
	int col = location.second;
	int nextRow = row;
	int nextCol = col;
	switch (dir)
	{
	case UP:
		nextRow = row - 1;
		if (nextRow == -1)
			nextRow = ROWS - 1;
		break;
	case DOWN:
		nextRow = row + 1;
		if (nextRow == ROWS)
			nextRow = 0;
		break;
	case LEFT:
		nextCol = col - 1;
		if (nextCol == -1)
			nextCol = COLS - 1;
		break;
	case RIGHT:
		nextCol = col + 1;
		if (nextCol == COLS)
			nextCol = 0;
		break;
	default:
		break;
	}

	gameObject obj = getInMap(nextRow, nextCol);
	
	if (obj != gameObject::WALL)
	{
		setGameMap(row, col, obj);
		setGameMap(nextRow, nextCol, gameObject::RED_GHOST);
		location = pair<int, int>(nextRow, nextCol);
	}

}
