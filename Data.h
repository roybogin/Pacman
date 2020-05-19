#pragma once
#pragma comment(lib,"ws2_32.lib")

#include <SFML/Graphics.hpp>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

enum gameObject { NOTHING = 0, COIN = 1, PLAYER = 2, WALL = 3, RED_GHOST = 4, BLUE_GHOST = 5, PINK_GHOST = 6, ORANGE_GHOST = 7, POWER_PELLET = 8, ONE_WAY_DOOR = 9 };
#include "Player.h"
#include "Ghost.h"
#include "Socket.h"

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
const int SPEED_CONST = 20;	//bigger const means slower game
const double SPEED = 0.25;
const int PELLET_TIME = 300;
const int PELLET_BLINK = 50;
const int NUMBER_OF_COINS = 242;
const bool MLSolver = false;
const std::string IP_ADDR = "127.0.0.1";
const PCSTR PORT = "2000";

extern int speedCount;
extern int score;
extern int ghostsEatenForPellet;
extern int coinsEaten;
extern int pelletsEaten;
extern int lives;
extern int gameMap[ROWS * COLS];
extern bool lost;
extern bool won;

extern RenderWindow window;
extern Font scoreFont;
extern Text scoreText;
extern Text scoreValueText;
extern Player player;
extern RedGhost redGhost;
extern BlueGhost blueGhost;
extern PinkGhost pinkGhost;
extern OrangeGhost orangeGhost;



const int startGameMap[ROWS * COLS] =
{
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
	3, 1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 1, 3,
	3, 8, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 8, 3,
	3, 1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 1, 3,
	3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
	3, 1, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 1, 3,
	3, 1, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 1, 3,
	3, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 3,
	3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3,
	0, 0, 0, 0, 0, 3, 1, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3, 3, 3, 3, 3, 1, 3, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 3, 1, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 1, 3, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 3, 1, 3, 3, 0, 3, 3, 3, 9, 9, 3, 3, 3, 0, 3, 3, 1, 3, 0, 0, 0, 0, 0,
	3, 3, 3, 3, 3, 3, 1, 3, 3, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 3, 3, 1, 3, 3, 3, 3, 3, 3,
	0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
	3, 3, 3, 3, 3, 3, 1, 3, 3, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 3, 3, 1, 3, 3, 3, 3, 3, 3,
	0, 0, 0, 0, 0, 3, 1, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 1, 3, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 3, 1, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 1, 3, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 3, 1, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 1, 3, 0, 0, 0, 0, 0,
	3, 3, 3, 3, 3, 3, 1, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 1, 3, 3, 3, 3, 3, 3,
	3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
	3, 1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 1, 3,
	3, 1, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 1, 3,
	3, 8, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 8, 3,
	3, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 3,
	3, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 1, 3, 3, 3,
	3, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 1, 3,
	3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3,
	3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3,
	3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
};