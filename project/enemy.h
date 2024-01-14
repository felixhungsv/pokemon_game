#pragma once
#include "Pokemon.h"
#include "Pokemonlist.h"

class Enemy : public Pokemon
{
private:
public:
    Enemy(const int chosenPokemon)
        : Pokemon(PokemonName[chosenPokemon], PokemonStats[chosenPokemon],
                  Pos[PokemonStats[chosenPokemon][2 * POKEMON_STATS_NUM]], PokemonSkills[chosenPokemon]){};
    // Enemy(const Enemy &enemy);
    ~Enemy(){};
    int chooseChosenSkill();
    void setDifficulty(int difficulty) { level = difficulty; };
    void die();

    void attackMode(/* Pokemon &target */){};
    bool chooseSkill(int input);
};