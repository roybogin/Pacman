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
	bool isDead = false;
	int powerPelletTime = 0;
	bool isInGhostHouse;
	bool canGetOut;
public:
	virtual void move() = 0;
	void chooseDirection();
	bool canChangeDirection(direction d);
	virtual void setTarget() = 0;
	void setIsDead(bool dead);
	bool getIsDead();
	void setPelletTime(int time);
	int getPelletTime();
	gameObject getOnSquare();
	std::pair<int, int> getLocation();
	void allowGetOut();
	bool getCanGetOut();
};

class RedGhost : public Ghost
{
private:
	
public:
	RedGhost();
	virtual void setTarget();
	virtual void move();
};

class BlueGhost : public Ghost
{
private:

public:
	BlueGhost();
	virtual void setTarget();
	virtual void move();
};

class PinkGhost : public Ghost
{
private:

public:
	PinkGhost();
	virtual void setTarget();
	virtual void move();
};

class OrangeGhost : public Ghost
{
private:

public:
	OrangeGhost();
	virtual void setTarget();
	virtual void move();
};