#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include <random>
#include <memory>
#include "player.h"
#include "enemy.h"
#include "battle.h"
#include "color.h"
#include "skill.h"
#include "Pokemon.h"
using namespace std;

int difficulty = 1;
const int incidentNum = 6;
vector<vector<string> /**/> incidents(6);

Battle::Battle(shared_ptr<Player> player, shared_ptr<Enemy> enemy) : round(1)
{
    leftUseLimit.resize(2, vector<int>(4, 0));
    skills.resize(2);
    Hp.resize(2);
    this->fighters.push_back(player);
    this->fighters.push_back(enemy);
    this->fighters[0]->getUseLimit(leftUseLimit[0]);
    this->fighters[1]->getUseLimit(leftUseLimit[1]);
    Hp[0] = this->fighters[0]->getHealth();
    Hp[1] = this->fighters[1]->getHealth();
}

Battle::~Battle()
{
    for (int i = 0; i < fighters.size(); i++)
        fighters[i]->clearAfterBattle();
}

string stringMoving(string str, int count)
{
    if (count == 0)
        return str;
    int strlen = str.length();
    string newStr;
    for (int i = count; i < strlen + count; i++)
        newStr += str[i % strlen];
    return newStr;
}
string stringMoving(string str, int count, int length)
{
    int strlen = str.length();
    string newStr;
    for (int i = count; i < length + count; i++)
        newStr += str[i % strlen];
    return newStr;
}

void Battle::printStartBanner(int second)
{
    chrono::seconds last(second);
    chrono::duration<double, milli> pass(0), interval(15);
    int count = 0, strlen;
    string GO1 = "GO GO GO GO GO GO GO GO GO GO GO GO ";
    string GO2 = " GO GO GO GO GO GO GO GO GO GO GO GO";
    string PokemonGo = "   BATTLE START!      POKEMON GO!   ";
    strlen = GO1.length();
    string PokemonNames, playerName = fighters[0]->getName(), enemyName = fighters[1]->getName();
    for (int i = 0; i < (strlen - 4 - playerName.length() - enemyName.length() + 1) / 2; i++)
        PokemonNames += ' ';
    PokemonNames += playerName + " vs " + enemyName;
    for (int i = 0; i < (strlen - 4 - playerName.length() - enemyName.length()) / 2; i++)
        PokemonNames += ' ';

    cout << "\0337";
    while (!(pass >= last && count % strlen == 1))
    {
        cout << "\0338\n\n\033[1m"
             << BACKGROUND_COLOR << CRIMSON << TEXT_COLOR << LIGHTPINK << stringMoving(GO1, count % strlen) << RESET << '\n'
             << BACKGROUND_COLOR << LIGHTYELLOW << setw(strlen) << ' ' << RESET << '\n'
             << BACKGROUND_COLOR << LIGHTYELLOW << TEXT_COLOR << BLACK << "\033[1m" << stringMoving(PokemonNames, count % strlen) << RESET << '\n'
             << BACKGROUND_COLOR << LIGHTYELLOW << setw(strlen) << ' ' << RESET << '\n'
             << BACKGROUND_COLOR << LIGHTYELLOW << TEXT_COLOR << BLACK << "\033[1m" << stringMoving(PokemonGo, count % strlen) << RESET << '\n'
             << BACKGROUND_COLOR << LIGHTYELLOW << setw(strlen) << ' ' << RESET << '\n'
             << BACKGROUND_COLOR << BLUE << TEXT_COLOR << SKYBLUE << "\033[1m" << stringMoving(GO2, count % strlen) << RESET << "\n\n\n"
             << flush;
        this_thread::sleep_for(interval);
        pass += interval;
        count++;
        interval += chrono::duration<double, milli>(cbrt(2 * count) * 0.07);
    }
    return;
}

void Battle::startBattle()
{
    chrono::duration<double, milli> interval(100);
    int count = 1;
    string str = " ROUND " + to_string(round) + " ";
    int strlen = str.length();
    for (int i = 0; i < strlen; i++)
        str.insert(str.begin(), ' ');
    while (count <= strlen)
    {
        cout << "\0338\033[J\033[1m" << TEXT_COLOR << WHITE << BACKGROUND_COLOR << RED
             << stringMoving(str, count, strlen)
             << flush;
        this_thread::sleep_for(interval);
        count++;
    }
    this_thread::sleep_for(5 * interval);
    cout << RESET << "\n\n"
         << "Choose your skill!\n\n";
    this_thread::sleep_for(10 * interval);
    fighters[0]->printChosenSkills(leftUseLimit[0]);
    cout << endl;
    // incidents
    if (randomNum(1, 100) <= 30)
        this->incidentHappen();
    round++;
}

int Battle::enemyChooseSkill()
{
    return fighters[1]->chooseChosenSkill();
}

int Battle::attack()
{
    cout << "\033[J\n";
    int ret = 0;
    int whofirst = whoFirst(fighters, fighters[0]->getSkill(skills[0]), fighters[1]->getSkill(skills[1]));
    double damage;
    bool attacked = 0;

    for (int i = 0; i < 2; i++)
    {
        this->PokeAtk(whofirst, damage, ret);
        if (!attacked)
            if (fighters[whofirst]->getSkill(skills[whofirst])->getName() == "HeadBut")
                if (randomNum(1, 100) <= 30)
                {
                    fighters[abs(whofirst - 1)]->stun();
                    cout << fighters[abs(whofirst - 1)]->getName() << " is stunned!\n";
                }
        cout << endl;
        this_thread::sleep_for(chrono::seconds(2));
        whofirst = abs(whofirst - 1);
        attacked = 1;
    }

    for (int i = 0; i < 2; i++)
    {
        if (ret == 0)
            if (fighters[whofirst]->getStatus().isBurn())
            {
                cout << fighters[whofirst]->getName() << " is burned, losing its Hp!" << endl;
                this_thread::sleep_for(chrono::seconds(1));
                if (this->computeHp(fighters[whofirst]->getHealth() / 16, Hp[whofirst], fighters[whofirst]))
                    ret = -1;
                cout << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }
        whofirst = abs(whofirst - 1);
    }
    cout << endl;

    cout << fighters[0]->getName() << "'s Hp" << setw(11 - fighters[0]->getName().length()) << right << ": ";
    cout << "\n\n";
    cout << fighters[1]->getName() << "'s Hp" << setw(11 - fighters[1]->getName().length()) << right << ": " << flush;
    cout << "\033[2F\033[16C";
    this_thread::sleep_for(chrono::milliseconds(500));
    printHp(Hp[0], fighters[0]->getHealth(), 1);
    cout << "\033[2E\033[16C";
    this_thread::sleep_for(chrono::milliseconds(500));
    printHp(Hp[1], fighters[1]->getHealth(), 0);
    cout << "\n\n";
    if (ret == 1)
    {
        // win
        difficulty++;
        fighters[0]->levelUp();
        printFallingWin();
    }
    else if (ret == -1)
    {
        // lose
        printFallingLose();
    }
    for (int i = 0; i < 2; i++)
        fighters[i]->clearBuff();
    return ret;
}

void Battle::PokeAtk(int whoFirst, double &damage, int &ret)
{
    damage = fighters[whoFirst]->useSkill(skills[whoFirst], fighters[abs(whoFirst - 1)], leftUseLimit[whoFirst][skills[whoFirst]]);
    if (fighters[whoFirst]->getSkill(skills[whoFirst])->rivalIsTarget())
    {
        if (this->computeHp(damage, Hp[abs(whoFirst - 1)], fighters[abs(whoFirst - 1)]))
            if (ret == 0)
            {
                if (whoFirst == 0)
                    ret = 1;
                else
                    ret = -1;
            }
        this_thread::sleep_for(chrono::seconds(2));
        if (fighters[whoFirst]->getSkill(skills[whoFirst])->getName() == "HornLeech")
            this->computeHp((-1) * damage / 2, Hp[whoFirst], fighters[whoFirst]);
        if (fighters[whoFirst]->getSkill(skills[whoFirst])->getName() == "TakeDown")
            this->computeHp(damage / 4, Hp[whoFirst], fighters[whoFirst]);
        if (fighters[whoFirst]->getSkill(skills[whoFirst])->getName() == "CloseCombat")
            fighters[whoFirst]->tempAbilityEffect(3, -1);
    }
    else
        this->computeHp(damage, Hp[whoFirst], fighters[whoFirst]);
}

int whoFirst(vector<shared_ptr<Pokemon> /**/> fighters, shared_ptr<Skill> playerSkill, shared_ptr<Skill> enemySkill)
{
    if (playerSkill->compareSpeed(enemySkill) == 1)
        return 0;
    double playerSpeed = fighters[0]->computeAbility(1), enemySpeed = fighters[1]->computeAbility(1);
    if (fighters[0]->getStatus().isParal())
        playerSpeed *= 0.5;
    if (fighters[1]->getStatus().isParal())
        enemySpeed *= 0.5;
    if (playerSpeed > enemySpeed)
        return 0;
    else if (playerSpeed < enemySpeed)
        return 1;
    else
    {
        random_device rd;
        mt19937 f(rd());
        uniform_int_distribution<> dis(1, 100);
        return (int)(dis(f) > 50);
    }
}

int Battle::getUsed(bool isplayer, int skill)
{
    if (isplayer)
        return leftUseLimit[0][skill];
    else
        return leftUseLimit[1][skill];
    return 0;
}

void printHp(double nowHp, double oriHp, bool isplayer)
{
    chrono::duration<int, ratio<1, 48> /**/> gap(1);
    if (isplayer)
        cout << BACKGROUND_COLOR << BLUE;
    else
        cout << BACKGROUND_COLOR << RED;
    for (int i = 0; i < int((nowHp / oriHp) * 32); i++)
    {
        this_thread::sleep_for(gap);
        cout << ' ' << flush;
    }
    if (isplayer)
        cout << BACKGROUND_COLOR << LIGHTBLUE;
    else
        cout << BACKGROUND_COLOR << PINK;
    for (int i = int((nowHp / oriHp) * 32); i < 32; i++)
    {
        this_thread::sleep_for(gap);
        cout << ' ' << flush;
    }
    cout << RESET;
}

void printWin()
{
    cout << "\033[1m";
    cout << TEXT_COLOR << BLUE << " __    __  _____    __  __   "
         << TEXT_COLOR << RED << "   __      __   ______   __    __   "
         << TEXT_COLOR << OLIVE << "   __     \n"
         << TEXT_COLOR << BLUE << "/\\ \\  /\\ \\/\\  __`\\ /\\ \\/\\ \\  "
         << TEXT_COLOR << RED << "  /\\ \\  __/\\ \\ /\\__  _\\ /\\ \\_,/\\ \\  "
         << TEXT_COLOR << OLIVE << "  /\\ \\    \n"
         << TEXT_COLOR << BLUE << "\\ `\\`\\\\/'/\\ \\ \\/\\ \\\\ \\ \\ \\ \\ "
         << TEXT_COLOR << RED << "  \\ \\ \\/\\ \\ \\ \\\\/_/\\ \\/ \\ \\  _`\\` \\ "
         << TEXT_COLOR << OLIVE << "  \\ \\ \\   \n"
         << TEXT_COLOR << BLUE << " `\\ `\\ /'  \\ \\ \\ \\ \\\\ \\ \\ \\ \\ "
         << TEXT_COLOR << RED << "  \\ \\ \\ \\ \\ \\ \\  \\ \\ \\  \\ \\ \\,\\_  \\  "
         << TEXT_COLOR << OLIVE << " \\ \\_\\  \n"
         << TEXT_COLOR << BLUE << "   `\\ \\ \\   \\ \\ \\_\\ \\\\ \\ \\_\\ \\  "
         << TEXT_COLOR << RED << " \\ \\ \\_/ \\_\\ \\  \\_\\ \\__\\ \\ \\_ `\\ \\ "
         << TEXT_COLOR << OLIVE << "  \\/_/_ \n"
         << TEXT_COLOR << BLUE << "     \\ \\_\\   \\ \\_____\\\\ \\_____\\ "
         << TEXT_COLOR << RED << "  \\ `\\___x___/  /\\_____\\\\ \\_\\`\\ \\_\\  "
         << TEXT_COLOR << OLIVE << "  /\\_\\\n"
         << TEXT_COLOR << BLUE << "      \\/_/    \\/_____/ \\/_____/  "
         << TEXT_COLOR << RED << "  '\\/__//__/   \\/_____/ \\/_/  \\/_/ "
         << TEXT_COLOR << OLIVE << "   \\/_/\n"
         << RESET << flush;
}
void printFallingWin()
{
    cout << "\033[7S\033[7F" << flush;
    chrono::duration<double, milli> interval(15);
    this_thread::sleep_for(chrono::milliseconds(1000));

    vector<string> YOU;
    YOU.push_back("      \\/_/    \\/_____/ \\/_____/  \n");
    YOU.push_back("     \\ \\_\\   \\ \\_____\\\\ \\_____\\ \n");
    YOU.push_back("   `\\ \\ \\   \\ \\ \\_\\ \\\\ \\ \\_\\ \\  \n");
    YOU.push_back(" `\\ `\\ /'  \\ \\ \\ \\ \\\\ \\ \\ \\ \\ \n");
    YOU.push_back("\\ `\\`\\\\/'/\\ \\ \\/\\ \\\\ \\ \\ \\ \\ \n");
    YOU.push_back("/\\ \\  /\\ \\/\\  __`\\ /\\ \\/\\ \\  \n");
    YOU.push_back(" __    __  _____    __  __   \n");
    cout << TEXT_COLOR << BLUE << BACKGROUND_COLOR << WHITE << "\033[1m";
    for (int i = 0; i < YOU.size(); i++)
    {
        if (i > 0)
            cout << "\033[" << i << "F\033J";
        for (int j = i; j >= 0; j--)
            cout << YOU[j];
        cout << flush;
        this_thread::sleep_for(interval * (sqrt(i + 1) - sqrt(i)));
    }

    this_thread::sleep_for(chrono::milliseconds(700));

    vector<string> WIN;
    WIN.push_back("    '\\/__//__/   \\/_____/ \\/_/  \\/_/ \n");
    WIN.push_back("   \\ `\\___x___/  /\\_____\\\\ \\_\\`\\ \\_\\  \n");
    WIN.push_back("  \\ \\ \\_/ \\_\\ \\  \\_\\ \\__\\ \\ \\_ `\\ \\ \n");
    WIN.push_back(" \\ \\ \\ \\ \\ \\ \\  \\ \\ \\  \\ \\ \\,\\_  \\  \n");
    WIN.push_back("\\ \\ \\/\\ \\ \\ \\\\/_/\\ \\/ \\ \\  _`\\` \\ \n");
    WIN.push_back("/\\ \\  __/\\ \\ /\\__  _\\ /\\ \\_,/\\ \\  \n");
    WIN.push_back(" __      __   ______   __    __   \n");
    cout << TEXT_COLOR << RED << BACKGROUND_COLOR << WHITE << "\033[1m\033[7F";
    for (int i = 0; i < WIN.size(); i++)
    {
        for (int j = 0; j < i; j++)
            cout << "\033[F\033[31C\033[K\033[31D";
        for (int j = i; j >= 0; j--)
            cout << "\033[31C" << WIN[j];
        cout << flush;
        this_thread::sleep_for(interval * (sqrt(i + 1) - sqrt(i)));
    }

    this_thread::sleep_for(chrono::milliseconds(700));

    vector<string> ex;
    ex.push_back("    \\/_/\n");
    ex.push_back("    /\\_\\\n");
    ex.push_back("  \\/_/_ \n");
    ex.push_back(" \\ \\_\\  \n");
    ex.push_back("\\ \\ \\   \n");
    ex.push_back("/\\ \\    \n");
    ex.push_back(" __     \n");
    cout << TEXT_COLOR << OLIVE << "\033[1m\033[7F";
    for (int i = 0; i < ex.size(); i++)
    {
        for (int j = 0; j < i; j++)
            cout << "\033[F\033[67C\033[K\033[67D";
        for (int j = i; j >= 0; j--)
            cout << "\033[67C" << ex[j];
        cout << flush;
        this_thread::sleep_for(interval * (sqrt(i + 1) - sqrt(i)));
    }

    cout << RESET;
}
void printLose()
{
    cout << "\033[1m";
    cout << TEXT_COLOR << BLUE << " __    __  _____    __  __   "
         << TEXT_COLOR << RED << "   __        _____    ______    _______    "
         << TEXT_COLOR << OLIVE << "  __     \n"
         << TEXT_COLOR << BLUE << "/\\ \\  /\\ \\/\\  __`\\ /\\ \\/\\ \\  "
         << TEXT_COLOR << RED << "  /\\ \\      /\\  __`\\ /\\  ___`\\  /\\  ____\\  "
         << TEXT_COLOR << OLIVE << " /\\ \\    \n"
         << TEXT_COLOR << BLUE << "\\ `\\`\\\\/'/\\ \\ \\/\\ \\\\ \\ \\ \\ \\ "
         << TEXT_COLOR << RED << "  \\ \\ \\     \\ \\ \\/\\ \\\\ \\,\\_L\\_\\\\ \\ \\___,/  "
         << TEXT_COLOR << OLIVE << " \\ \\ \\   \n"
         << TEXT_COLOR << BLUE << " `\\ `\\ /'  \\ \\ \\ \\ \\\\ \\ \\ \\ \\ "
         << TEXT_COLOR << RED << "  \\ \\ \\     \\ \\ \\ \\ \\\\/_\\___ \\ \\ \\  ___\\  "
         << TEXT_COLOR << OLIVE << "  \\ \\_\\  \n"
         << TEXT_COLOR << BLUE << "   `\\ \\ \\   \\ \\ \\_\\ \\\\ \\ \\_\\ \\  "
         << TEXT_COLOR << RED << " \\ \\ \\_____\\ \\ \\_\\ \\ /\\ \\_L\\ \\\\ \\ \\_,/___ "
         << TEXT_COLOR << OLIVE << " \\/_/_ \n"
         << TEXT_COLOR << BLUE << "     \\ \\_\\   \\ \\_____\\\\ \\_____\\ "
         << TEXT_COLOR << RED << "  \\ \\_____`\\\\ \\_____\\\\ `\\_____\\\\ \\_______\\ "
         << TEXT_COLOR << OLIVE << "  /\\_\\\n"
         << TEXT_COLOR << BLUE << "      \\/_/    \\/_____/ \\/_____/  "
         << TEXT_COLOR << RED << "  \\/_____`/ \\/_____/ \\/______/ \\/_______/ "
         << TEXT_COLOR << OLIVE << "  \\/_/\n"
         << RESET << flush;
}
void printFallingLose()
{
    cout << "\033[7S\033[7F" << flush;
    chrono::duration<double, milli> interval(15);
    this_thread::sleep_for(chrono::milliseconds(1000));

    vector<string> YOU;
    YOU.push_back("      \\/_/    \\/_____/ \\/_____/  \n");
    YOU.push_back("     \\ \\_\\   \\ \\_____\\\\ \\_____\\ \n");
    YOU.push_back("   `\\ \\ \\   \\ \\ \\_\\ \\\\ \\ \\_\\ \\  \n");
    YOU.push_back(" `\\ `\\ /'  \\ \\ \\ \\ \\\\ \\ \\ \\ \\ \n");
    YOU.push_back("\\ `\\`\\\\/'/\\ \\ \\/\\ \\\\ \\ \\ \\ \\ \n");
    YOU.push_back("/\\ \\  /\\ \\/\\  __`\\ /\\ \\/\\ \\  \n");
    YOU.push_back(" __    __  _____    __  __   \n");
    cout << TEXT_COLOR << BLUE << BACKGROUND_COLOR << WHITE << "\033[1m";
    for (int i = 0; i < YOU.size(); i++)
    {
        if (i > 0)
            cout << "\033[" << i << "F\033J";
        for (int j = i; j >= 0; j--)
            cout << YOU[j];
        cout << flush;
        this_thread::sleep_for(interval * (sqrt(i + 1) - sqrt(i)));
    }

    this_thread::sleep_for(chrono::milliseconds(500));

    vector<string> LOSE;
    LOSE.push_back("     \\/_____`/ \\/_____/ \\/______/ \\/_______/ \n");
    LOSE.push_back("    \\ \\_____`\\\\ \\_____\\\\ `\\_____\\\\ \\_______\\ \n");
    LOSE.push_back("   \\ \\ \\_____\\ \\ \\_\\ \\ /\\ \\_L\\ \\\\ \\ \\_,/___ \n");
    LOSE.push_back("  \\ \\ \\     \\ \\ \\ \\ \\\\/_\\___ \\ \\ \\  ___\\  \n");
    LOSE.push_back(" \\ \\ \\     \\ \\ \\/\\ \\\\ \\,\\_L\\_\\\\ \\ \\___,/  \n");
    LOSE.push_back("/\\ \\      /\\  __`\\ /\\  ___`\\  /\\  ____\\  \n");
    LOSE.push_back(" __        _____    ______    _______    \n");
    cout << TEXT_COLOR << RED << BACKGROUND_COLOR << WHITE << "\033[1m\033[7F";
    for (int i = 0; i < LOSE.size(); i++)
    {
        for (int j = 0; j < i; j++)
            cout << "\033[F\033[31C\033[K\033[31D";
        for (int j = i; j >= 0; j--)
            cout << "\033[31C" << LOSE[j];
        cout << flush;
        this_thread::sleep_for(interval * (sqrt(i + 1) - sqrt(i)));
    }

    this_thread::sleep_for(chrono::milliseconds(500));

    vector<string> ex;
    ex.push_back("    \\/_/\n");
    ex.push_back("    /\\_\\\n");
    ex.push_back("  \\/_/_ \n");
    ex.push_back(" \\ \\_\\  \n");
    ex.push_back("\\ \\ \\   \n");
    ex.push_back("/\\ \\    \n");
    ex.push_back(" __     \n");
    cout << TEXT_COLOR << OLIVE << "\033[1m\033[7F";
    for (int i = 0; i < ex.size(); i++)
    {
        for (int j = 0; j < i; j++)
            cout << "\033[F\033[75C\033[K\033[75D";
        for (int j = i; j >= 0; j--)
            cout << "\033[75C" << ex[j];
        cout << flush;
        this_thread::sleep_for(interval * (sqrt(i + 1) - sqrt(i)));
    }

    cout << RESET;
}

bool Battle::computeHp(double damage, double &targetHp, shared_ptr<Pokemon> target)
{
    if (damage < 0)
    {
        targetHp = min(target->getHealth(), targetHp - damage);
        cout << target->getName() << " has recovered!\n";
    }
    else if (damage > 0)
    {
        targetHp = max(0.0, targetHp - damage);
        if (int(targetHp) == 0)
        {
            cout << target->getName() << " was killed!\n";
            return 1;
        }
        else
            cout << target->getName() << " was injured!\n";
    }
    return 0;
}

void Battle::incidentHappen()
{
    int index = randomNum(0, 5);
    this_thread::sleep_for(chrono::seconds(1));
    cout << "It's \033[1m" << incidents[index][0] << "\033[m !!!" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout << incidents[index][1] << "!\n"
         << endl;
    this_thread::sleep_for(chrono::seconds(2));
    if (index == 0)
    {
        for (int i = 0; i < 2; i++)
            if (fighters[i]->getAttribute()->getName() == "mad")
            {
                fighters[i]->setBuff(2, 1.1);
                fighters[i]->setBuff(3, 1.2);
            }
    }
    else if (index == 1)
    {
        for (int i = 0; i < 2; i++)
            Hp[i] += (fighters[i]->getHealth() - Hp[i]) / 7;
    }
    else if (index == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            if (fighters[i]->getAttribute()->getName() == "water")
                fighters[i]->setBuff(2, 1.1);
            if (fighters[i]->getAttribute()->getName() == "fire")
                fighters[i]->setBuff(2, 0.8);
        }
    }
    else if (index == 3)
    {
        for (int i = 0; i < 2; i++)
        {
            if (fighters[i]->getAttribute()->getName() == "grass")
                fighters[i]->setBuff(3, 0.8);
            if (fighters[i]->getAttribute()->getName() == "fire")
                fighters[i]->setBuff(1, 1.2);
        }
    }
    else if (index == 4)
    {
        for (int i = 0; i < 2; i++)
        {
            if (fighters[i]->getAttribute()->getName() == "normal")
                for (int j = 1; j < POKEMON_STATS_NUM; j++)
                    fighters[i]->setBuff(j, 1.1);
        }
    }
    else if (index == 5)
    {
        for (int i = 0; i < 2; i++)
        {
            fighters[i]->setBuff(2, 0.8);
            fighters[i]->setBuff(3, 0.9);
        }
    }
}