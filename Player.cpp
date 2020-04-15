#include "Player.h"
#include "Data.h"
#include "Funcs.h"

Player::Player()
{
	location = pair<int, int>(23, 13);
	dir = LEFT;
}

std::pair<int, int> Player::getLocation()
{
	return location;
}

void Player::move()
{
	int row = location.first;
	int col = location.second;
	int nextRow = row;
	int nextCol = col;
	switch (dir)
	{
	case Player::UP:
		nextRow = row - 1;
		if (nextRow == -1)
			nextRow = ROWS - 1;
		break;
	case Player::DOWN:
		nextRow = row + 1;
		if (nextRow == ROWS)
			nextRow = 0;
		break;
	case Player::LEFT:
		nextCol = col - 1;
		if (nextCol == -1)
			nextCol = COLS-1;
		break;
	case Player::RIGHT:
		nextCol = col + 1;
		if (nextCol == COLS)
			nextCol = 0;
		break;
	default:
		break;
	}

	switch (getInMap(nextRow, nextCol))
	{
	case gameObject::NOTHING:
		setGameMap(row, col, gameObject::NOTHING);
		setGameMap(nextRow, nextCol, gameObject::PLAYER);
		location = pair<int, int>(nextRow, nextCol);
		break;
	case gameObject::COIN:
		setGameMap(row, col, gameObject::NOTHING);
		setGameMap(nextRow, nextCol, gameObject::PLAYER);
		location = pair<int, int>(nextRow, nextCol);
		score += 10;
		coinsEaten++;
		break;
	case gameObject::POWER_PELLET:
		setGameMap(row, col, gameObject::NOTHING);
		setGameMap(nextRow, nextCol, gameObject::PLAYER);
		location = pair<int, int>(nextRow, nextCol);
		score += 50;
		ghostsEatenForPellet = 0;
		redGhost.setPelletTime(PELLET_TIME);
		blueGhost.setPelletTime(PELLET_TIME);
		pinkGhost.setPelletTime(PELLET_TIME);
		orangeGhost.setPelletTime(PELLET_TIME);
		break;
	case gameObject::RED_GHOST:
		if (!redGhost.getIsDead())
		{
			if (redGhost.getPelletTime() == 0)
			{
				loseLife();
				return;
			}
			else
			{
				redGhost.setIsDead(true);
				redGhost.setPelletTime(0);
				ghostsEatenForPellet++;
				score += (pow(2, ghostsEatenForPellet) * 100);
			}
		}
		setGameMap(row, col, gameObject::NOTHING);
		setGameMap(nextRow, nextCol, gameObject::PLAYER);
		location = pair<int, int>(nextRow, nextCol);
		break;
	case gameObject::BLUE_GHOST:
		if (!blueGhost.getIsDead())
		{
			if (blueGhost.getPelletTime() == 0)
			{
				loseLife();
				return;
			}
			else
			{
				blueGhost.setIsDead(true);
				blueGhost.setPelletTime(0);
				ghostsEatenForPellet++;
				score += (pow(2, ghostsEatenForPellet) * 100);
			}
		}
		setGameMap(row, col, gameObject::NOTHING);
		setGameMap(nextRow, nextCol, gameObject::PLAYER);
		location = pair<int, int>(nextRow, nextCol);
		break;
	case gameObject::PINK_GHOST:
		if (!pinkGhost.getIsDead())
		{
			if (pinkGhost.getPelletTime() == 0)
			{
				loseLife();
				return;
			}
			else
			{
				pinkGhost.setIsDead(true);
				pinkGhost.setPelletTime(0);
				ghostsEatenForPellet++;
				score += (pow(2, ghostsEatenForPellet) * 100);
			}
		}
		setGameMap(row, col, gameObject::NOTHING);
		setGameMap(nextRow, nextCol, gameObject::PLAYER);
		location = pair<int, int>(nextRow, nextCol);
		break;
	case gameObject::ORANGE_GHOST:
		if (!orangeGhost.getIsDead())
		{
			if (orangeGhost.getPelletTime() == 0)
			{
				loseLife();
				return;
			}
			else
			{
				orangeGhost.setIsDead(true);
				orangeGhost.setPelletTime(0);
				ghostsEatenForPellet++;
				score += (pow(2, ghostsEatenForPellet) * 100);
			}
		}
		setGameMap(row, col, gameObject::NOTHING);
		setGameMap(nextRow, nextCol, gameObject::PLAYER);
		location = pair<int, int>(nextRow, nextCol);
		break;
	case gameObject::WALL:
		break;
	}	

}

bool Player::canChangeDirection(direction d)
{
	int row = location.first;
	int col = location.second;
	int nextRow = row;
	int nextCol = col;
	switch (d)
	{
	case Player::UP:
		nextRow = row - 1;
		if (nextRow == -1)
			nextRow = ROWS - 1;
		break;
	case Player::DOWN:
		nextRow = row + 1;
		if (nextRow == ROWS)
			nextRow = 0;
		break;
	case Player::LEFT:
		nextCol = col - 1;
		if (nextCol == -1)
			nextCol = COLS - 1;
		break;
	case Player::RIGHT:
		nextCol = col + 1;
		if (nextCol == COLS)
			nextCol = 0;
		break;
	default:
		break;
	}
	return (getInMap(nextRow, nextCol) != gameObject::WALL && getInMap(nextRow, nextCol) != gameObject::ONE_WAY_DOOR);
}

void Player::setDirection(direction d)
{
	dir = d;
}

Player::direction Player::getDirection()
{
	return dir;
}

void Player::setMouthOpen(bool b)
{
	isMouthOpen = b;
}

bool Player::getMouthOpen()
{
	return isMouthOpen;
}