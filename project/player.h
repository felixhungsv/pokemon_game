#pragma once
#include <vector>
#include "Pokemon.h"
#include "Pokemonlist.h"
#include "skill.h"
using namespace std;

const int LEVEL_EXP = 100;

class Player : public Pokemon
{
private:
public:
    Player(const int chosenPokemon)
        : Pokemon(PokemonName[chosenPokemon], PokemonStats[chosenPokemon],
                  Pos[PokemonStats[chosenPokemon][2 * POKEMON_STATS_NUM]], PokemonSkills[chosenPokemon]){};
    // Player(const Player &player);
    ~Player(){};

    vector<int> getPos();
    void levelUp();
    int move(string str);
    void printSkills(const int num, vector<int> &skillPool);
    void printChosenSkills(vector<int> uselimit);
    void printChosenSkillsName();

    void attackMode(/* Pokemon &target */){};
    bool chooseSkill(int input);
};