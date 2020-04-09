#pragma once
#include "Data.h"

vector<Shape*> getShape(int row, int col);
gameObject getInMap(int row, int col);
void setGameMap(int row, int col, gameObject object);