#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <memory>
#include <thread>
#include <chrono>
#include "Pokemon.h"
#include "attribute.h"
#include "skill.h"
using namespace std;

Pokemon::Pokemon(vector<string> PokemonName, vector<int> PokemonStats, vector<int> Pos, vector<int /**/> skills) : level(1)
{
    name = PokemonName[0];
    for (int i = 0; i < ATTRIBUTE_NUM; i++)
        if (attributeList[i]->getName() == PokemonName[1])
            attribute = attributeList[i];
    for (int i = 0; i < POKEMON_STATS_NUM; i++)
        ability.push_back(PokemonStats[i]);
    this->position = vector<int>(2);
    for (int i = 0; i < Pos.size(); i++)
        this->position[i] = Pos[i];
    for (int i = 0; i < skills.size(); i++)
        relatedSkill.push_back(skillList[skills[i]]);
    for (int i = POKEMON_STATS_NUM; i < 2 * POKEMON_STATS_NUM; i++)
        levelUpStats.push_back(PokemonStats[i]);
    for (int i = 0; i < POKEMON_STATS_NUM; i++)
    {
        tempAbility.push_back(0);
        tempAbilityBuff.push_back(1);
    }
}

void Pokemon::getUseLimit(vector<int> &list)
{
    for (int i = 0; i < chosenSkills.size(); i++)
        list[i] = relatedSkill[chosenSkills[i]]->getUselimit();
}

void Pokemon::printPos()
{
    cout << name << " is at" << '\n'
         << "x: " << position[0] << '\n'
         << "y: " << position[1] << '\n';
    return;
}

string Pokemon::getSkillName(int index)
{
    return relatedSkill[chosenSkills[index]]->getName();
}

double Pokemon::computeAbility(int index)
{
    if (tempAbility[index] > 0)
        return (ability[index] + (level - 1) * levelUpStats[index]) * (double(2 + tempAbility[index]) / 2.0) * tempAbilityBuff[index];
    else if (tempAbility[index] < 0)
        return (ability[index] + (level - 1) * levelUpStats[index]) * (2.0 / double(2 + abs(tempAbility[index]))) * tempAbilityBuff[index];
    return (ability[index] + (level - 1) * levelUpStats[index]) * tempAbilityBuff[index];
}

double Pokemon::useSkill(int index, shared_ptr<Pokemon> target, int &uselimit)
{
    if (this->isControlled(index) || this->isStun())
        return 0;
    cout << name << " used " << this->getSkillName(index) << "...\n";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "and...\n";
    this_thread::sleep_for(chrono::seconds(1));
    if (relatedSkill[chosenSkills[index]]->checkAtk())
    {
        uselimit--;
        if (!this->getSkill(index)->isAssistant())
        {
            if (this->getSkill(index)->getName() == "HydroCannon" || this->getSkill(index)->getName() == "BlastBurn" || this->getSkill(index)->getName() == "FrenzyPlant" || this->getSkill(index)->getName() == "HyperBeam" || this->getSkill(index)->getName() == "MeteorAssault")
                this->stun();
            if (this->getSkill(index)->getName() == "FirePunch" || this->getSkill(index)->getName() == "Flamethrower" || this->getSkill(index)->getName() == "FireBlast")
                if (randomNum(1, 100) <= 10)
                    if (target->addStatus(0))
                        cout << target->getName() << " get burned!\n";
            double buff;
            if (this->getAttribute()->getName() == "mad")
                buff = 2.0;
            else if (target->getAttribute()->getName() == "mad")
                buff = 2.0;
            else if (this->getAttribute()->getName() == "normal" || target->getAttribute()->getName() == "normal")
                buff = 1.0;
            else
                buff = relatedSkill[chosenSkills[index]]->getAttribute()->attributeEffect(target->getAttribute());
            if (this->getAttribute()->getName() == this->getSkill(index)->getAttribute()->getName())
                buff *= 1.5;
            if (this->getStatus().isBurned)
                buff *= 0.8;
            return (double)(((double)(7 * level + 10) / 250) * (this->computeAbility(2) / target->computeAbility(3)) * (relatedSkill[chosenSkills[index]]->getPower()) + 2) * buff * randomNum(0.85, 1.0);
        }
        else
            return this->getSkill(index)->useAssistant(target);
    }
    else
        cout << "MISS!\n";
    return 0;
}

void Pokemon::clearAfterBattle()
{
    chosenSkills.clear();
    for (int i = 0; i < POKEMON_STATS_NUM; i++)
        tempAbility[i] = 0;
    status.clear();
}

void Pokemon::selectSkills(int num, vector<int> &skillPool)
{
    int assNum = randomNum(0, 2);
    if (assNum > 0)
    {
        vector<int> ass;
        for (int i = 0; i < relatedSkill.size(); i++)
            if (relatedSkill[i]->isAssistant())
                ass.push_back(i);
        vectorShuffle(ass);
        for (int i = 0; i < assNum; i++)
            skillPool.push_back(ass[i]);
    }
    num -= assNum;
    vector<int> v;
    for (int i = 0; i < relatedSkill.size(); i++)
        if (!relatedSkill[i]->isAssistant())
            v.push_back(i);
    vectorShuffle(v);
    for (int i = 0; i < num; i++)
        skillPool.push_back(v[i]);
    sort(skillPool);
}

bool Pokemon::addStatus(int sta)
{
    if (!status.isStatus)
    {
        status.isStatus = 1;
        if (sta == 0)
            status.isBurned = 1;
        else if (sta == 1)
            status.isFrozen = 3;
        else if (sta == 2)
            status.isParalyzed = 1;
        else if (sta == 3)
            status.isSleeping = randomNum(1, 3);
        return 1;
    }
    return 0;
}

bool Pokemon::isControlled(int index)
{
    if (status.isFrozen > 0)
    {
        if (relatedSkill[chosenSkills[index]]->getAttribute()->getName() == "fire" || relatedSkill[chosenSkills[index]]->getAttribute()->getName() == "mad" || randomNum(1, 100) <= 20)
        {
            cout << name << " is unfrozen!\n";
            this_thread::sleep_for(chrono::seconds(1));
            status.isFrozen = 0;
            return 0;
        }
        status.isFrozen--;
        cout << name << " is frozen! It's too cold to move!\n";
        return 1;
    }
    if (status.isParalyzed)
    {
        if (randomNum(1, 100) <= 25)
        {
            cout << name << " is paralyzed! Cannot move!\n";
            this_thread::sleep_for(chrono::seconds(1));
            return 1;
        }
        return 0;
    }
    if (status.isSleeping > 0)
    {
        cout << name << " is sleeping! Do not disturb!\n";
        this_thread::sleep_for(chrono::seconds(1));
        return 1;
    }
    return 0;
}

bool Pokemon::isStun()
{
    if (status.isStunned)
    {
        cout << name << " is stunned! Cannot move!\n";
        status.isStunned = 0;
        this_thread::sleep_for(chrono::seconds(1));
        return 1;
    }
    return 0;
}

void Pokemon::tempAbilityEffect(int ability, int stage)
{
    tempAbility[ability] += stage;
    if (tempAbility[ability] > 6)
        tempAbility[ability] = 6;
    else if (tempAbility[ability] < -6)
        tempAbility[ability] = -6;
}

void Pokemon::setBuff(int ability, double buff)
{
    tempAbilityBuff[ability] *= buff;
}

void Pokemon::clearBuff()
{
    for (int i = 0; i < POKEMON_STATS_NUM; i++)
        tempAbilityBuff[i] = 1;
}

void sort(vector<int> &v)
{
    vector<int> t;
    t.push_back(v[0]);
    for (int i = 1; i < v.size(); i++)
    {
        bool in = 0;
        for (int j = 0; j < t.size(); j++)
        {
            if (v[i] < t[j])
            {
                t.insert(t.begin() + j, v[i]);
                in = 1;
                break;
            }
        }
        if (!in)
            t.push_back(v[i]);
    }
    v = t;
}

int randomNum(int lower, int upper)
{
    random_device rd;
    mt19937 f(rd());
    uniform_int_distribution<> dis(lower, upper);
    return dis(f);
}
double randomNum(double lower, double upper)
{
    random_device rd;
    mt19937 f(rd());
    uniform_real_distribution<> dis(lower, upper);
    return dis(f);
}

void Status::clear()
{
    isStatus = 0;
    isBurned = 0;
    isParalyzed = 0;
    isFrozen = 0;
    isSleeping = 0;
    isStunned = 0;
}

template <typename T>
void vectorShuffle(vector<T> &v)
{
    random_device rd;
    mt19937 f(rd());
    shuffle(v.begin(), v.end(), f);
}