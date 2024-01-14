#include <iostream>
#include <random>
#include <vector>
#include "enemy.h"
#include "map.h"
using namespace std;

void Enemy::die()
{
    map[position[0]][position[1]] = 6;
}

int Enemy::chooseChosenSkill()
{
    if (status.isFreeze() > 0)
        for (int i = 0; i < chosenSkills.size(); i++)
            if (relatedSkill[chosenSkills[i]]->getAttribute()->getName() == "mad" || relatedSkill[chosenSkills[i]]->getAttribute()->getName() == "fire")
                return i;
    random_device rd;
    mt19937 f(rd());
    uniform_int_distribution<> dis(0, 3);
    return dis(f);
}

bool Enemy::chooseSkill(int input)
{
    vector<int> v;
    for (int i = 0; i < relatedSkill.size(); i++)
        v.push_back(i);

    random_device rd;
    mt19937 f(rd());
    shuffle(v.begin(), v.end(), f);

    for (int i = 0; i < 4; i++)
        chosenSkills.push_back(v[i]);

    return 0;
}
