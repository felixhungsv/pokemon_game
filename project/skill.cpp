#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <random>
#include <thread>
#include <chrono>
#include "skill.h"
#include "Pokemonlist.h"
#include "attribute.h"
#include "color.h"
#include "Pokemon.h"
using namespace std;

vector<shared_ptr<Skill> /**/> skillList;
vector<vector<int /**/> /**/> PokemonSkills(POKEMON_NUM);

Skill::Skill(string nm, string atr, vector<int> stats)
{
    name = nm;
    for (int i = 0; i < ATTRIBUTE_NUM; i++)
        if (attributeList[i]->getName() == atr)
            attribute = attributeList[i];
    for (int i = 0; i < stats.size(); i++)
        this->stats.push_back(stats[i]);
    if (this->stats[3] > 0)
        skillTags.prior = 1;
    else
        skillTags.prior = 0;
    if (this->stats[0] == 0)
        skillTags.assistant = 1;
    else
        skillTags.assistant = 0;
}

/*Skill::Skill(Skill &skill)
{
    name = skill.name;
    attribute = skill.attribute;
    power = skill.power;
    uselimit = skill.uselimit;
    precision = skill.precision;
    speed = skill.speed;
    controlment = skill.controlment;
}*/

void Skill::print(int i)
{
    cout << setw(3) << left << i << setw(16) << name << "Attr: " << attribute->getName() << '\n'
         << setw(3) << " "
         << "Power: " << setw(9) << stats[0] << "UseLimit: " << stats[1] << '\n'
         << setw(3) << " "
         << "Precision: " << setw(5) << stats[2] << "Speed: " << stats[3] << '\n'
         << setw(3) << " " << skillDescription[0] << "\n\n";
}
void Skill::print(int i, shared_ptr<Skill> skill)
{
    int height = max(skillDescription.size(), skill->skillDescription.size());

    this->attribute->atrPrintColor(0);
    cout << setw(48) << " " << RESET << '\n';
    this->attribute->atrPrintColor(1);
    cout << "  " << setw(3) << left << i << setw(18) << name << "Attr: " << setw(19) << attribute->getName() << RESET << '\n';
    this->attribute->atrPrintColor(1);
    cout << setw(5) << " "
         << "Power: " << setw(11) << stats[0] << "UseLimit: " << setw(15) << stats[1] << RESET << '\n';
    this->attribute->atrPrintColor(1);
    cout << setw(5) << " "
         << "Precision: " << setw(7) << stats[2] << "Speed: " << setw(18) << stats[3] << RESET << '\n';
    this->attribute->atrPrintColor(0);
    cout << setw(48) << " " << RESET << '\n';
    for (int i = 0; i < skillDescription.size(); i++)
    {
        this->attribute->atrPrintColor(0);
        cout << setw(5) << " " << setw(43) << skillDescription[i] << RESET << '\n';
    }
    for (int i = 0; i <= height - skillDescription.size(); i++)
    {
        this->attribute->atrPrintColor(0);
        cout << setw(48) << " " << RESET << endl;
    }

    skill->getAttribute()->atrPrintColor(0);
    cout << "\033[" << 6 + height << "F\033[50C" << setw(48) << " " << RESET << '\n';
    skill->getAttribute()->atrPrintColor(1);
    cout << "\033[50C  " << setw(3) << i + 1 << setw(18) << skill->name << "Attr: " << setw(19) << skill->attribute->getName() << RESET << '\n';
    skill->getAttribute()->atrPrintColor(1);
    cout << "\033[50C" << setw(5) << " "
         << "Power: " << setw(11) << skill->stats[0] << "UseLimit: " << setw(15) << skill->stats[1] << RESET << '\n';
    skill->getAttribute()->atrPrintColor(1);
    cout << "\033[50C" << setw(5) << " "
         << "Precision: " << setw(7) << skill->stats[2] << "Speed: " << setw(18) << skill->stats[3] << RESET << '\n';
    skill->getAttribute()->atrPrintColor(0);
    cout << "\033[50C" << setw(48) << " " << RESET << '\n';
    for (int i = 0; i < skill->skillDescription.size(); i++)
    {
        skill->getAttribute()->atrPrintColor(0);
        cout << "\033[50C" << setw(5) << " " << setw(43) << skill->skillDescription[i] << RESET << '\n';
    }
    for (int i = 0; i <= height - skill->skillDescription.size(); i++)
    {
        skill->getAttribute()->atrPrintColor(0);
        cout << "\033[50C" << setw(48) << " " << RESET << endl;
    }

    this_thread::sleep_for(chrono::duration<int, milli>(500));
}
void Skill::print(int i, int uselimit)
{
    cout << setw(3) << left << i << setw(16) << name << "Attr: " << attribute->getName() << '\n'
         << setw(3) << " "
         << "Power: " << setw(9) << stats[0] << "UseLimit: " << uselimit << '\n'
         << setw(3) << " "
         << "Precision: " << setw(5) << stats[2] << "Speed: " << stats[3] << '\n'
         << setw(3) << " " << skillDescription[0] << "\n\n";
}
void Skill::print(int i, int luselimit, shared_ptr<Skill> skill, int ruselimit)
{
    int height = max(skillDescription.size(), skill->skillDescription.size());

    this->attribute->atrPrintColor(0);
    cout << setw(48) << " " << RESET << '\n';
    this->attribute->atrPrintColor(1);
    cout << "  " << setw(3) << left << i << setw(18) << name << "Attr: " << setw(19) << attribute->getName() << RESET << '\n';
    this->attribute->atrPrintColor(1);
    cout << setw(5) << " "
         << "Power: " << setw(11) << stats[0] << "UseLimit: " << setw(15) << luselimit << RESET << '\n';
    this->attribute->atrPrintColor(1);
    cout << setw(5) << " "
         << "Precision: " << setw(7) << stats[2] << "Speed: " << setw(18) << stats[3] << RESET << '\n';
    this->attribute->atrPrintColor(0);
    cout << setw(48) << " " << RESET << '\n';
    for (int i = 0; i < skillDescription.size(); i++)
    {
        this->attribute->atrPrintColor(0);
        cout << setw(5) << " " << setw(43) << skillDescription[i] << RESET << '\n';
    }
    for (int i = 0; i <= height - skillDescription.size(); i++)
    {
        this->attribute->atrPrintColor(0);
        cout << setw(48) << " " << RESET << endl;
    }

    this_thread::sleep_for(chrono::duration<int, milli>(500));

    skill->getAttribute()->atrPrintColor(0);
    cout << "\033[" << 6 + height << "F\033[50C" << setw(48) << " " << RESET << '\n';
    skill->getAttribute()->atrPrintColor(1);
    cout << "\033[50C  " << setw(3) << i + 1 << setw(18) << skill->name << "Attr: " << setw(19) << skill->attribute->getName() << RESET << '\n';
    skill->getAttribute()->atrPrintColor(1);
    cout << "\033[50C" << setw(5) << " "
         << "Power: " << setw(11) << skill->stats[0] << "UseLimit: " << setw(15) << ruselimit << RESET << '\n';
    skill->getAttribute()->atrPrintColor(1);
    cout << "\033[50C" << setw(5) << " "
         << "Precision: " << setw(7) << skill->stats[2] << "Speed: " << setw(18) << skill->stats[3] << RESET << '\n';
    skill->getAttribute()->atrPrintColor(0);
    cout << "\033[50C" << setw(48) << " " << RESET << '\n';
    for (int i = 0; i < skill->skillDescription.size(); i++)
    {
        skill->getAttribute()->atrPrintColor(0);
        cout << "\033[50C" << setw(5) << " " << setw(43) << skill->skillDescription[i] << RESET << '\n';
    }
    for (int i = 0; i <= height - skill->skillDescription.size(); i++)
    {
        skill->getAttribute()->atrPrintColor(0);
        cout << "\033[50C" << setw(48) << " " << RESET << endl;
    }

    this_thread::sleep_for(chrono::duration<int, milli>(500));
}

void Skill::addDescription(string des)
{
    skillDescription.push_back(des);
}

bool Skill::checkAtk()
{
    random_device rd;
    mt19937 f(rd());
    uniform_int_distribution<> dis(1, 100);

    if (dis(f) <= stats[2])
        return 1;
    return 0;
}

int Skill::compareSpeed(shared_ptr<Skill> skill)
{
    if (this->skillTags.prior == 1)
    {
        if (skill->skillTags.prior == 0)
            return 1;
        if (this->stats[4] > skill->stats[4])
            return 1;
        else if (this->stats[4] < skill->stats[4])
            return -1;
        return 0;
    }
    if (skill->skillTags.prior == 1)
        return -1;
    if (stats[3] > skill->stats[3])
        return 1;
    else if (stats[3] < skill->stats[3])
        return -1;
    else
        return 0;
}

double Skill::useAssistant(shared_ptr<Pokemon> target)
{
    if (this->getName() == "Onibi")
    {
        if (!target->isStatus())
        {
            target->addStatus(0);
            cout << target->getName() << " is burned by a sinister flame!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "Its attack would reduce by 20 % and it'd lose 1/16 of its max HP each round.\n";
        }
        else
            cout << target->getName() << " has been in abnormal status.\n";
    }
    else if (this->getName() == "Recover")
        return (-1) * target->getHealth() / 2;
    else if (this->getName() == "IcyWind")
    {
        if (!target->isStatus())
        {
            target->addStatus(1);
            cout << target->getName() << " is frozen by chilled air!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "It is allowed to use fire or mad skills only, and after using one of them, it'd be unfrozen.\n";
        }
        else
            cout << target->getName() << " has been in abnormal status.\n";
    }
    else if (this->getName() == "ThunderWave")
    {
        if (!target->isStatus())
        {
            cout << target->getName() << " is paralyzed by a weak jolt of electricity!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "It'd become slower by 50% and has a 25% chance of not being able to attack.\n";
            target->addStatus(2);
        }
        else
            cout << target->getName() << " has been in abnormal status.\n";
    }
    else if (this->getName() == "Spore")
    {
        if (!target->isStatus())
        {
            cout << target->getName() << " is hypnotized by bursts of spores!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "It'd be sleeping for 1-3 rounds and cannot move while sleeping!\n";
            target->addStatus(3);
        }
        else
            cout << target->getName() << " has been in abnormal status.\n";
    }
    return 0.0;
}

void setSkill(ifstream &lnput)
{
    string nm, atr, sstr;
    int intput;
    for (int i = 0; i < SKILL_NUM; i++)
    {
        vector<int> stats;
        lnput >> nm >> atr;
        for (int j = 0; j < SKILL_STATS_NUM; j++)
        {
            lnput >> intput;
            stats.push_back(intput);
        }
        shared_ptr<Skill> skill = make_shared<Skill>(nm, atr, stats);
        skillList.push_back(skill);
        lnput.ignore(1000, '\n');
        getline(lnput, nm);
        while (nm != "end")
        {
            skill->addDescription(nm);
            getline(lnput, nm);
        }
        if (skill->isPrior())
            skill->addDescription("This is a prior skill.");
        for (int j = 0; j < POKEMON_NUM; j++)
            if (PokemonName[j][1] != skill->getAttribute()->getProAttribute()->getName())
                PokemonSkills[j].push_back(i);
    }
    return;
}
