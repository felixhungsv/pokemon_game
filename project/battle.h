#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "player.h"
#include "enemy.h"
#include "Pokemon.h"
using namespace std;

extern int difficulty;
extern const int incidentNum;
extern vector<vector<string> /**/> incidents;

int whoFirst(vector<shared_ptr<Pokemon> /**/> fighters, shared_ptr<Skill> playerSkill, shared_ptr<Skill> enemySkill);
void printHp(double nowHp, double oriHp, bool isplayer);
void printWin();
void printFallingWin();
void printLose();
void printFallingLose();

class Battle
{
private:
    vector<shared_ptr<Pokemon> /**/> fighters;
    vector<double> Hp;
    int round;
    vector<vector<int> /**/> leftUseLimit;
    vector<int> skills;

public:
    Battle(shared_ptr<Player> player, shared_ptr<Enemy> enemy);
    ~Battle();
    void printStartBanner(int second);
    void startBattle();
    int enemyChooseSkill();
    double getPlayerHp() { return Hp[0]; };
    double getEnemyHp() { return Hp[1]; };
    int attack();
    void PokeAtk(int whoFirst, double &damage, int &ret);
    void setSkill(int index0, int index1)
    {
        skills[0] = index0;
        skills[1] = index1;
    };
    int getUsed(bool isplayer, int skill);
    bool computeHp(double damage, double &targetHp, shared_ptr<Pokemon> target);
    void incidentHappen();
};