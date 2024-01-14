#pragma once
#include <vector>
#include <memory>
#include "attribute.h"
#include "Pokemonlist.h"
#include "skill.h"
using namespace std;

class Skill;
class Pokemon;

class Status
{
private:
    bool isStatus;
    bool isBurned;
    int isFrozen;
    bool isParalyzed;
    int isSleeping;
    bool isStunned;

public:
    Status() : isStatus(0), isBurned(0), isParalyzed(0), isFrozen(0), isSleeping(0), isStunned(0){};
    void clear();
    bool isBurn() { return isBurned; };
    bool isParal() { return isParalyzed; };
    int isFreeze() { return isFrozen; };

    friend class Pokemon;
};

void sort(vector<int> &v);
extern int randomNum(int lower, int upper);
extern double randomNum(double lower, double upper);
template <typename T>
void vectorShuffle(vector<T> &v);

class Pokemon
{
protected:
    string name;
    shared_ptr<Attribute> attribute;
    vector<double> ability;
    vector<int> position;
    vector<shared_ptr<Skill> /**/> relatedSkill;
    vector<int> chosenSkills;
    vector<int> levelUpStats;
    vector<int> tempAbility;
    vector<double> tempAbilityBuff;
    int level;
    Status status;

public:
    Pokemon(vector<string> PokemonName, vector<int> PokemonStats, vector<int> Pos, vector<int /**/> skills);
    ~Pokemon(){};
    double getHealth() { return ability[0] + (level - 1) * levelUpStats[0]; };
    string getName() { return name; };
    int getSkillNum() { return relatedSkill.size(); };
    void getUseLimit(vector<int> &list);
    void printPos();
    string getSkillName(int index);
    double computeAbility(int index);
    int getLevel() { return level; };
    double useSkill(int index, shared_ptr<Pokemon> target, int &uselimit);
    void clearAfterBattle();
    shared_ptr<Skill> getSkill(int index) { return relatedSkill[chosenSkills[index]]; };
    shared_ptr<Attribute> getAttribute() { return attribute; };
    void selectSkills(int num, vector<int> &skillPool);
    bool isStatus() { return status.isStatus; };
    bool addStatus(int sta);
    bool isControlled(int index);
    bool isStun();
    void stun() { status.isStunned = 1; };
    Status getStatus() { return status; };
    void tempAbilityEffect(int ability, int stage);
    void setBuff(int ability, double buff);
    void clearBuff();

    virtual void printSkills(const int num, vector<int> &skillPool){};
    virtual void printChosenSkills(vector<int> uselimit){};
    virtual void levelUp(){};
    virtual int chooseChosenSkill() { return 0; };

    virtual void attackMode(/* Pokemon &target */) = 0;
    virtual bool chooseSkill(int input) = 0;
};
