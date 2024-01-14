#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include "Pokemonlist.h"
#include "color.h"
using namespace std;

vector<vector<string> /**/> PokemonName(POKEMON_NUM, vector<string>(POKEMON_NAME_NUM, ""));
vector<vector<int> /**/> PokemonStats(POKEMON_NUM, vector<int>(2 * POKEMON_STATS_NUM + 1, 0));
vector<vector<int> /**/> Pos(POKEMON_NUM, vector<int>(2, 0));

void setData(ifstream &input)
{
    int intput;
    string strinput;
    for (int i = 0; i < POKEMON_NUM; i++)
    {
        input >> intput;
        for (int j = 0; j < POKEMON_NAME_NUM; j++)
        {
            input >> strinput;
            PokemonName[i][j] = strinput;
        }
        for (int j = 0; j < 2 * POKEMON_STATS_NUM; j++)
        {
            input >> intput;
            PokemonStats[i][j] = intput;
        }
    }
    return;
}

bool choosePokemon(int num)
{
    cout << "\033[F\033[JYou've chosen " << PokemonName[num][0] << "!" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    printImg(PokemonName[num][0]);
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Let's go!" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return 0;
}

void setPos(const int chosenPokemon)
{
    vector<int> v;
    for (int i = 1; i < POKEMON_NUM; i++)
        v.push_back(i);

    random_device rd;
    mt19937 f(rd());
    shuffle(v.begin(), v.end(), f);

    int c = 0;
    for (int i = 0; i < POKEMON_NUM; i++)
        if (i != chosenPokemon)
        {
            PokemonStats[i][2 * POKEMON_STATS_NUM] = v[c];
            c++;
        }
    return;
}

int checkPokemon(vector<int> pos)
{
    for (int i = 0; i < POKEMON_NUM; i++)
        if (Pos[PokemonStats[i][2 * POKEMON_STATS_NUM]][0] == pos[0] && Pos[PokemonStats[i][2 * POKEMON_STATS_NUM]][1] == pos[1])
            return i;
    return -1;
}

void printImg(string name)
{
    string str = "viu -t -w 40 ./image/" + name + ".png";
    char *ch = new char[50];
    strcpy(ch, str.c_str());
    int a = system(ch);
    delete[] ch;
    ch = nullptr;
}