#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Ghost.h"

using namespace std;
using namespace sf;

class Player;
class RedGhost;

const int playerRadius = 10;
const int ROWS = 31;
const int COLS = 28;
const int BLOCK_SIZE = 30;
const int BG_WIDTH = BLOCK_SIZE * COLS;
const int BG_HEIGHT = BLOCK_SIZE * ROWS;
const int SPEED = 20;

extern int speedCount;
extern int score;
enum gameObject { NOTHING = 0, COIN = 1, PLAYER = 2, WALL = 3, RED_GHOST = 4, BLUE_GHOST = 5, PINK_GHOST = 6, ORANGE_GHOST = 7};
extern int gameMap[ROWS * COLS];

extern RenderWindow window;
extern Player player;
extern RedGhost redGhost;
