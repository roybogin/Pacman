#pragma once
#include <SFML/Graphics.hpp>
#include "Data.h"

class Ghost
{
public:
	enum direction { UP, DOWN, LEFT, RIGHT };
protected:
	std::pair<int, int> location;
	direction dir;
	std::pair<int, int> target;
	gameObject onSquare;
public:
	void move() = 0;
	void chooseDirection();
	bool canChangeDirection(direction d);
	virtual void setTarget() = 0;
};

class RedGhost : public Ghost
{
private:
	
public:
	RedGhost();
	virtual void setTarget();
	virtual void move();
};