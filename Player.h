#pragma once
#include <SFML/Graphics.hpp>
#include "Data.h"

class Player
{
public:
	enum direction { UP, DOWN, LEFT, RIGHT };
private:
	std::pair<int, int> location;
	direction dir;
public:
	Player();
	std::pair<int, int> getLocation();
	void setDirection(direction d);
	void move();
	bool canChangeDirection(direction d);
	direction getDirection();
};