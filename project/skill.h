#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include "attribute.h"
#include "Pokemon.h"
using namespace std;

const int SKILL_NUM = 25;
const int SKILL_STATS_NUM = 6;

void setSkill(ifstream &lnput);

class Pokemon;

struct Tag
{
    bool prior;
    bool assistant;
};

class Skill
{
private:
    string name;
    shared_ptr<Attribute> attribute;
    // power uselimit precision speed controlment isRival
    vector<int> stats;
    vector<string> skillDescription;
    Tag skillTags;

public:
    Skill(string nm, string atr, vector<int> stats);
    // Skill(Skill &skill);
    void print(int i);
    void print(int i, shared_ptr<Skill> skill);
    void print(int i, int uselimit);
    void print(int i, int luselimit, shared_ptr<Skill> skill, int ruselimit);
    void addDescription(string des);
    string getName() { return name; };
    int getUselimit() { return stats[1]; };
    int getPower() { return stats[0]; };
    bool checkAtk();
    int compareSpeed(shared_ptr<Skill> skill);
    shared_ptr<Attribute> getAttribute() { return attribute; };
    bool isAssistant() { return skillTags.assistant; };
    bool isPrior() { return skillTags.prior; };
    double useAssistant(shared_ptr<Pokemon> rival);
    bool rivalIsTarget() { return (bool)(stats[5]); };
};

extern vector<shared_ptr<Skill> /**/> skillList;
extern vector<vector<int /**/> /**/> PokemonSkills;
