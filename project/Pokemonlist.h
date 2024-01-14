#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Pokemon.h"
using namespace std;

const int POKEMON_NUM = 10;
const int POKEMON_NAME_NUM = 2;
const int POKEMON_STATS_NUM = 4;
extern vector<vector<string> /**/> PokemonName;
extern vector<vector<int> /**/> PokemonStats;
extern vector<vector<int> /**/> Pos;

void setData(ifstream &input);
void setPos(const int chosenPokemon);
bool choosePokemon(int num);
int checkPokemon(vector<int> pos);
extern void printImg(string name);
