#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "player.h"
using namespace std;

const int MAP_X = 25;
const int MAP_Y = 25;
const int PRINT_RANGE = 3;
extern vector<vector<int> /**/> map;

void setMap(ifstream &inmap);
void printMap(vector<int> pos);
