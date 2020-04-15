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

const int ROWS = 31;
const int COLS = 28;
const int STARTING_ROWS = 3;
const int ENDING_ROWS = 2;
const int BLOCK_SIZE = 30;
const int BG_WIDTH = BLOCK_SIZE * COLS;
const int BG_HEIGHT = BLOCK_SIZE * (STARTING_ROWS + ROWS + ENDING_ROWS);
const int SPEED_CONST = 20;
const double PLAYER_SPEED = 0.25;
const double GHOST_SPEED = 1.0/3;
const int PELLET_TIME = 300;
const int NUMBER_OF_COINS = 242;

extern int speedCount;
extern int score;
extern int ghostsEatenForPellet;
extern int coinsEaten;
extern int lives;
extern int gameMap[ROWS * COLS];
extern bool gameOver;

extern RenderWindow window;
extern Font scoreFont;
extern Text scoreText;
extern Text scoreValueText;
extern Player player;
extern RedGhost redGhost;
extern BlueGhost blueGhost;
extern PinkGhost pinkGhost;
extern OrangeGhost orangeGhost;