#include "Ghost.h"
#include "Data.h"
#include "Funcs.h"


bool Ghost::canChangeDirection(Ghost::direction d)
{
	switch (dir)
	{
	case Ghost::UP:	//can't turn back
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
		if (nextRow == -1)
			nextRow = ROWS - 1;
		break;
	case Ghost::DOWN:
		nextRow = row + 1;
		if (nextRow == ROWS)
			nextRow = 0;
		break;
	case Ghost::LEFT:
		nextCol = col - 1;
		if (nextCol == -1)
			nextCol = COLS - 1;
		break;
	case Ghost::RIGHT:
		nextCol = col + 1;
		if (nextCol == COLS)
			nextCol = 0;
		break;
	default:
		break;
	}
	if (getInMap(nextRow, nextCol) == gameObject::WALL)
		return false;
	if (getInMap(nextRow, nextCol) != gameObject::ONE_WAY_DOOR)
		return true;
	if (isDead)
		return true;
	return d == UP;
}

void Ghost::chooseDirection()	//minimum distance to target
{
	pair<int, int> nextLoc = location;
	bool changed = false;
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

	if (canChangeDirection(RIGHT))
	{
		nextLoc = pair<int, int>(location.first, location.second + 1);
		dist = sqrt(pow(nextLoc.first - target.first, 2) + pow(nextLoc.second - target.second, 2));
		if (dist < minLen)
		{
			minLen = dist;
			minDir = RIGHT;
		}
	}

	dir = minDir;

}

void Ghost::setIsDead(bool dead)
{
	isDead = dead;
}

bool Ghost::getIsDead()
{
	return isDead;
}

void Ghost::setPelletTime(int time)
{
	powerPelletTime = time;
}

int Ghost::getPelletTime()
{
	return powerPelletTime;
}

gameObject Ghost::getOnSquare()
{
	return onSquare;
}



///////////////////////RED///////////////////////

RedGhost::RedGhost()
{
	location = pair<int, int>(11, 14);
	dir = LEFT;
	onSquare = gameObject::NOTHING;
	isInGhostHouse = false;
}

void RedGhost::setTarget()
{
	if (!isDead)
	{
		if (isInGhostHouse)
			target = std::pair<int, int>(11, 13);
		else
			target = player.getLocation();
	}
	else
	{
		target = std::pair<int, int>(14, 13);
	}
}

void RedGhost::move()
{
	if (powerPelletTime == 0)
	{
		setTarget();
		chooseDirection();
	}
	else
	{
		vector<direction> possibleDir;
		if (canChangeDirection(UP))
			possibleDir.push_back(UP);
		if (canChangeDirection(DOWN))
			possibleDir.push_back(DOWN);
		if (canChangeDirection(LEFT))
			possibleDir.push_back(LEFT);
		if (canChangeDirection(RIGHT))
			possibleDir.push_back(RIGHT);
		dir = possibleDir[rand() % possibleDir.size()];
	}
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

	if (onSquare == ONE_WAY_DOOR && dir == UP)
	{
		isInGhostHouse = false;
	}

	if (obj == gameObject::COIN || obj == gameObject::POWER_PELLET || obj == gameObject::NOTHING)
	{
		setGameMap(row, col, onSquare);
		onSquare = obj;
		setGameMap(nextRow, nextCol, gameObject::RED_GHOST);
		location = pair<int, int>(nextRow, nextCol);
	}
	if (obj == gameObject::ONE_WAY_DOOR)
	{
		setGameMap(row, col, onSquare);
		onSquare = obj;
		setGameMap(nextRow, nextCol, gameObject::RED_GHOST);
		location = pair<int, int>(nextRow, nextCol);
		isInGhostHouse = true;
		if (dir == DOWN)
			isDead = false;
	}
	if (obj == gameObject::PLAYER)
	{
		if (!isDead)
		{
			if (powerPelletTime == 0)
				exit(0);
			else
			{
				isDead = true;
				powerPelletTime = 0;
			}
		}
		setGameMap(row, col, onSquare);
		onSquare = NOTHING;
		setGameMap(nextRow, nextCol, gameObject::RED_GHOST);
		location = pair<int, int>(nextRow, nextCol);
	}
	if (obj == gameObject::BLUE_GHOST)
	{
		setGameMap(row, col, onSquare);
		onSquare = blueGhost.getOnSquare();
		setGameMap(nextRow, nextCol, gameObject::RED_GHOST);
		location = pair<int, int>(nextRow, nextCol);
	}

}

pair<int, int> RedGhost::getLocation()
{
	return location;
}

///////////////////////BLUE///////////////////////

BlueGhost::BlueGhost()
{
	location = pair<int, int>(14, 12);
	dir = LEFT;
	onSquare = gameObject::NOTHING;
	isInGhostHouse = true;
}

void BlueGhost::setTarget()
{
	if (!isDead)
	{
		if (isInGhostHouse)
			target = std::pair<int, int>(11, 13);
		else
		{
			pair<int, int> playerLocation = player.getLocation();
			switch (player.getDirection())
			{
			case Player::UP:
				playerLocation.first -= 2;
				break;
			case Player::DOWN:
				playerLocation.first += 2;
				break;
			case Player::LEFT:
				playerLocation.second -= 2;
				break;
			case Player::RIGHT:
				playerLocation.second += 2;
				break;
			default:
				break;
			}
			pair<int, int> redLocation = redGhost.getLocation();
			target = pair<int, int>(playerLocation.first * 2 - redLocation.first, playerLocation.second * 2 - redLocation.second);
		}
	}
	else
	{
		target = std::pair<int, int>(14, 13);
	}
}

void BlueGhost::move()
{
	if (powerPelletTime == 0)
	{
		setTarget();
		chooseDirection();
	}
	else
	{
		vector<direction> possibleDir;
		if (canChangeDirection(UP))
			possibleDir.push_back(UP);
		if (canChangeDirection(DOWN))
			possibleDir.push_back(DOWN);
		if (canChangeDirection(LEFT))
			possibleDir.push_back(LEFT);
		if (canChangeDirection(RIGHT))
			possibleDir.push_back(RIGHT);
		dir = possibleDir[rand() % possibleDir.size()];
	}
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

	if (onSquare == ONE_WAY_DOOR && dir == UP)
	{
		isInGhostHouse = false;
	}

	if (obj == gameObject::COIN || obj == gameObject::POWER_PELLET || obj == gameObject::NOTHING)
	{
		setGameMap(row, col, onSquare);
		onSquare = obj;
		setGameMap(nextRow, nextCol, gameObject::BLUE_GHOST);
		location = pair<int, int>(nextRow, nextCol);
	}
	if (obj == gameObject::ONE_WAY_DOOR)
	{
		setGameMap(row, col, onSquare);
		onSquare = obj;
		setGameMap(nextRow, nextCol, gameObject::BLUE_GHOST);
		location = pair<int, int>(nextRow, nextCol);
		isInGhostHouse = true;
		if (dir == DOWN)
			isDead = false;
	}
	if (obj == gameObject::PLAYER)
	{
		if (!isDead)
		{
			if (powerPelletTime == 0)
				exit(0);
			else
			{
				isDead = true;
				powerPelletTime = 0;
			}
		}
		setGameMap(row, col, onSquare);
		onSquare = NOTHING;
		setGameMap(nextRow, nextCol, gameObject::BLUE_GHOST);
		location = pair<int, int>(nextRow, nextCol);
	}
	if (obj == gameObject::RED_GHOST)
	{
		setGameMap(row, col, onSquare);
		onSquare = redGhost.getOnSquare();
		setGameMap(nextRow, nextCol, gameObject::RED_GHOST);
		location = pair<int, int>(nextRow, nextCol);
	}
}
