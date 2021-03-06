#pragma once
#include "Data.h"

vector<Shape*> getShapes(int row, int col);
gameObject getInMap(int row, int col);
void setGameMap(int row, int col, gameObject object);
void loseLife();
float getXForTextInMiddle(Text text);
void drawLives();
bool coinOrPelletInGame();
void resetGameMap();
string getMLValue(int obj);