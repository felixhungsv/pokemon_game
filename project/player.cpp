#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include "player.h"
#include "map.h"
#include "Pokemonlist.h"
#include "skill.h"
using namespace std;

/* Player::Player(const Player &player)
{
    name = player->name;
    attribute = player->attribute;
    health = player->health;
    speed = player->speed;
    attack = player->attack;
    defend = player->defend;
    this->position = nullptr;
    for (int i = 0; i < skills.size(); i++)
        relatedSkill.push_back(player->relatedSkill[i]);
    level=player->level;
    experience
} */

vector<int> Player::getPos()
{
    return position;
}

void Player::levelUp()
{
    level += 1;
    return;
}

int Player::move(string str)
{
    bool crush = 0;
    vector<int> newpos(2);
    newpos[0] = position[0];
    newpos[1] = position[1];
    if (map[newpos[0]][newpos[1]] == 2)
        map[newpos[0]][newpos[1]] = 0;
    if (str.find_first_of("wasdWASD") != string::npos)
    {
        for (int i = str.find_first_of("wasdWASD"); i < str.length(); i++)
        {
            if (str[i] == 'w' || str[i] == 'W')
            {
                if (map[newpos[0]][newpos[1] - 1] <= 1)
                    newpos[1] -= 1;
                else
                    crush = 1;
            }
            else if (str[i] == 's' || str[i] == 'S')
            {
                if (map[newpos[0]][newpos[1] + 1] <= 1)
                    newpos[1] += 1;
                else
                    crush = 1;
            }
            else if (str[i] == 'a' || str[i] == 'A')
            {
                if (map[newpos[0] - 1][newpos[1]] <= 1)
                    newpos[0] -= 1;
                else
                    crush = 1;
            }
            else if (str[i] == 'd' || str[i] == 'D')
            {
                if (map[newpos[0] + 1][newpos[1]] <= 1)
                    newpos[0] += 1;
                else
                    crush = 1;
            }
        }
    }
    else
    {
        cout << "\033[F\033[J\033[EPLEASE ENTER SOMETHING CONTAINING \"WASD\"!\033[F";
        return -1;
    }

    printMap(newpos);
    if (crush)
        cout << "\033[EYou've crushed on the walls!\033[F";
    if (map[newpos[0]][newpos[1]] == 1)
    {
        int n = checkPokemon(newpos);
        if (n != -1)
        {
            cout << flush;
            this_thread::sleep_for(chrono::seconds(1));
            printImg(PokemonName[n][0]);
            this_thread::sleep_for(chrono::seconds(1));
            cout << "You've met "
                 << PokemonName[n][0] << "." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "Do you want to have a battle with "
                 << PokemonName[n][0]
                 << "?" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "Enter Y/N\n";
            position[0] = newpos[0];
            position[1] = newpos[1];
            return n;
        }
    }
    position[0] = newpos[0];
    position[1] = newpos[1];
    map[position[0]][position[1]] = 2;
    return -1;
}

void Player::printSkills(const int num, vector<int> &skillPool)
{
    this->selectSkills(num, skillPool);
    for (int i = 0; i < num; i += 2)
    {
        relatedSkill[skillPool[i]]->print(i + 1, relatedSkill[skillPool[i + 1]]);
        cout << '\n';
    }
}

void Player::printChosenSkills(vector<int> uselimit)
{
    for (int i = 0; i < chosenSkills.size(); i += 2)
    {
        relatedSkill[chosenSkills[i]]->print(i + 1, uselimit[i], relatedSkill[chosenSkills[i + 1]], uselimit[i + 1]);
        cout << '\n';
    }
}

void Player::printChosenSkillsName()
{
    for (int i = 0; i < chosenSkills.size(); i++)
        cout << relatedSkill[chosenSkills[i]]->getName() << ' ';
}

bool Player::chooseSkill(int input)
{
    for (int i = 0; i < chosenSkills.size(); i++)
        if (chosenSkills[i] == input)
        {
            cout << "\033[F\033[J\033[E";
            cout << "You've enter a repeated number!\033[F";
            return 0;
        }
    chosenSkills.push_back(input);
    cout << "\033[J";
    return 1;
}
