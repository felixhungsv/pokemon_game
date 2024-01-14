#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <memory>
#include "attribute.h"
#include "Pokemon.h"
#include "skill.h"
#include "player.h"
#include "Pokemonlist.h"
#include "map.h"
#include "enemy.h"
#include "color.h"
#include "battle.h"
using namespace std;

const int DISPLAY_SKILL_NUM = 8;

#define CHECK_INT                                                                                    \
    cin >> intput;                                                                                   \
    if (cin.fail() || floor(intput) != ceil(intput))                                                 \
    {                                                                                                \
        cin.clear();                                                                                 \
        cin.ignore(1000, '\n');                                                                      \
        cout << "\033[F\033[J\033[E"                                                                 \
             << "Please enter integers between " << lowerbound << " and " << upperbound << "\033[F"; \
        continue;                                                                                    \
    }                                                                                                \
    else if (int(intput) < lowerbound || int(intput) > upperbound)                                   \
    {                                                                                                \
        cin.ignore(1000, '\n');                                                                      \
        cout << "\033[F\033[J\033[E"                                                                 \
             << "Please enter numbers between " << lowerbound << " and " << upperbound << "\033[F";  \
        continue;                                                                                    \
    }                                                                                                \
    else                                                                                             \
        cin.ignore(1000, '\n');

#define IGNORE_NEWLINE          \
    if (cin.peek() == '\n')     \
    {                           \
        cin.ignore(1000, '\n'); \
        cout << "\033[F";       \
        continue;               \
    }

// 選技能
#define CHOOSE_SKILLS                                                        \
    cout << "Choose your skill set!\nYou can choose four of the below!\n\n"; \
    vector<int> skillPool;                                                   \
    player->printSkills(DISPLAY_SKILL_NUM, skillPool);                       \
    cout << "\nEach time choose one to build your skill set!\n";             \
    bool skillCheck = 0;                                                     \
    int skillNum = 0;                                                        \
    while (skillNum < 4)                                                     \
    {                                                                        \
        IGNORE_NEWLINE;                                                      \
        int lowerbound = 1, upperbound = DISPLAY_SKILL_NUM;                  \
        double intput;                                                       \
        CHECK_INT;                                                           \
        skillCheck = player->chooseSkill(skillPool[int(intput) - 1]);        \
        if (skillCheck)                                                      \
            skillNum++;                                                      \
    }                                                                        \
    cout << "\nYou've chosen: ";                                             \
    player->printChosenSkillsName();                                         \
    cout << "!\n\n";

string str_tolower(string s);

int main()
{
    // 載入所有Pokemon資訊、所有技能資訊
    ifstream input("PokemonList.txt");
    if (input)
    {
        setData(input);
        input.close();
    }
    setAttributes();
    ifstream lnput("skills.txt");
    if (lnput)
    {
        setSkill(lnput);
        lnput.close();
    }
    ifstream incput("incidents.txt");
    if (lnput)
    {
        string str;
        for (int i = 0; i < incidentNum; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                getline(incput, str);
                incidents[i].push_back(str);
            }
        }
        incput.close();
    }

    // 展示所有Pokemon
    cout << "\033[?25l\n\033[1m";
    printColor(" Choose your ", WHITE, BLUE, 0);
    printColor(" Pokemon ", WHITE, RED, 1);
    cout << "\n\n";
    cout << setw(3) << ' ' << left
         << setw(12) << "Name"
         << setw(12) << "Attribute"
         << setw(5) << "HP"
         << setw(5) << "SPD"
         << setw(5) << "ATK"
         << setw(5) << "DEF" << '\n'
         << '\n';
    for (int i = 0; i < POKEMON_NUM; i++)
    {
        cout << left << setw(3) << i + 1;
        for (int j = 0; j < POKEMON_NAME_NUM; j++)
            cout << left << setw(12) << PokemonName[i][j];
        for (int j = 0; j < POKEMON_STATS_NUM; j++)
            cout << left << setw(5) << PokemonStats[i][j];
        cout << '\n';
    }
    cout << '\n';

    // 玩家選擇Pokemon
    int chosenPokemon = 0;
    bool err = 0, keep = 1;
    while (keep)
    {
        IGNORE_NEWLINE;
        int lowerbound = 1, upperbound = POKEMON_NUM;
        double intput;
        CHECK_INT;
        chosenPokemon = int(intput) - 1;
        keep = choosePokemon(chosenPokemon);
    }

    // 載入地圖，並將玩家與敵人的位置寫入
    ifstream inmap("map.txt");
    if (inmap)
    {
        setMap(inmap);
        inmap.close();
    }
    setPos(chosenPokemon);

    // 建立玩家與敵人資訊
    shared_ptr<Player> player = make_shared<Player>(chosenPokemon);
    vector<shared_ptr<Enemy> /**/> enemies;
    for (int i = 0; i < POKEMON_NUM; i++)
        if (i != chosenPokemon)
        {
            shared_ptr<Enemy> enemy = make_shared<Enemy>(i);
            enemy->chooseSkill(1);
            enemies.push_back(enemy);
        }
        else
            enemies.push_back(nullptr);

    // 玩家開始移動
    cout << "\n\nPress Enter to continue...\n";
    cin.ignore(1000, '\n');
    cout << "Note that: '▼' means where you are now, while '@' means enemies' position.\n"
         << "You can use 'W', 'S', 'A', 'D' to controll your character to go up, down, left, and right.\n"
         << "If you want to leave, enter \"end\"!\n\0337";
    printMap(player->getPos());

    bool keepgoing = 1;
    int battle = 0;
    string str;
    while (keepgoing)
    {
        IGNORE_NEWLINE;
        getline(cin, str);
        if (str_tolower(str) == "end")
        {
            cout << "\033[F\033[J"
                 << "DO YOU REALLY WANT TO LEAVE???\n"
                 << "If yes, press ENTER!\n";
            char end = cin.get();
            if (end == '\n')
            {
                cout << "\033[?25h";
                keepgoing = 0;
                break;
            }
            cin.ignore(1000, '\n');
            cout << "\033[3F\033[J";
            continue;
        }
        battle = player->move(str);

        // 若移動到敵人位置，可選擇是否對戰
        while (battle != -1)
        {
            string s;
            getline(cin, s);
            if (s == "Y" || s == "y")
            {
                // 玩家選擇技能庫
                CHOOSE_SKILLS;
                cout << "Difficulty: " << difficulty << '\n';
                enemies[battle]->setDifficulty(difficulty);
                Battle bat(player, enemies[battle]);
                this_thread::sleep_for(chrono::seconds(2));
                bat.printStartBanner(5);
                cout << "Press ENTER to continue!\033[F";
                getline(cin, s);
                cout << "\033[F\033[J\033[E\n";
                err = 1;
                int result = 0;
                cout << "\0337";

                // 遊戲開始
                while (result == 0)
                {
                    this_thread::sleep_for(chrono::seconds(1));
                    bat.startBattle();
                    double intput;
                    while (err)
                    {
                        IGNORE_NEWLINE;
                        int lowerbound = 1, upperbound = 4;
                        CHECK_INT;
                        intput = int(intput) - 1;
                        if (bat.getUsed(1, int(intput)) == 0)
                        {
                            cout << "\033[F\033[J\033[E"
                                 << "You've run out the use limit of this skill.\nReselect your skill!\033[2F";
                            continue;
                        }
                        err = 0;
                    }
                    err = 1;
                    int enemySkill = bat.enemyChooseSkill();
                    bat.setSkill(int(intput), enemySkill);
                    result = bat.attack();
                    if (result == 1)
                    {
                        this_thread::sleep_for(chrono::seconds(2));
                        cout << "\n\n"
                             << enemies[battle]->getName() << " has been defeated!" << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        cout << "Congrats! Your level is up!" << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        cout << "But you've got to encounter more powerful enemies!" << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        cout << "Be careful!" << flush;
                        enemies[battle]->die();
                    }
                    else if (result == -1)
                    {
                        this_thread::sleep_for(chrono::seconds(2));
                        cout << "\n\nYou've been defeated!" << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        cout << "But do not give up!" << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        cout << "Try another strategy next time." << endl;
                        this_thread::sleep_for(chrono::seconds(2));
                        cout << "Good luck!" << flush;
                    }
                    this_thread::sleep_for(chrono::seconds(2));
                    cout << "\n\nPress ENTER to continue!\033[F";
                    getline(cin, s);
                }
                cout << "\0337";
                printMap(player->getPos());
                break;
            }
            else if (s == "N" || s == "n")
            {
                cout << "\033[24F\033[J";
                break;
            }
            else
            {
                cout << "\033[2F\033[J"
                     << "Please enter Y/N\n";
            }
        }
    }

    return 0;
}

string str_tolower(string s)
{
    for (int i = 0; i < s.length(); i++)
        s[i] = tolower(s[i]);
    return s;
}
