#pragma once
#include <SFML/Graphics.hpp>
enum gameObject { NOTHING = 0, COIN = 1, PLAYER = 2, WALL = 3, RED_GHOST = 4, BLUE_GHOST = 5, PINK_GHOST = 6, ORANGE_GHOST = 7, POWER_PELLET = 8, ONE_WAY_DOOR = 9 };
#include "Player.h"
#include "Ghost.h"

using namespace std;
using namespace sf;

class Player;
class RedGhost;
class BlueGhost;
class PinkGhost;
class OrangeGhost;

const int playerRadius = 10;
const int ROWS = 31;
const int COLS = 28;
const int BLOCK_SIZE = 30;
const int BG_WIDTH = BLOCK_SIZE * COLS;
const int BG_HEIGHT = BLOCK_SIZE * ROWS;
const int PLAYER_SPEED = 20;
const int GHOST_SPEED = 15;
const int PELLET_TIME = 150;

extern int speedCount;
extern int score;
extern int gameMap[ROWS * COLS];

extern RenderWindow window;
extern Player player;
extern RedGhost redGhost;
extern BlueGhost blueGhost;
extern PinkGhost pinkGhost;
//extern OrangeGhost orangeGhost;
