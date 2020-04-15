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
	bool isMouthOpen;
public:
	Player();
	std::pair<int, int> getLocation();
	void setDirection(direction d);
	void move();
	bool canChangeDirection(direction d);
	direction getDirection();
	void setMouthOpen(bool open);
	bool getMouthOpen();
};