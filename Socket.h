#pragma once
#include "Data.h"

void socketCreate();
void socketConnect();
void socketSend(const char* data);
std::string socketRecv();