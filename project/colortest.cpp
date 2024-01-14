/* #include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <random>
#include <cstdlib>
#include "AudioFile.h"
using namespace std;

#define TEXT_COLOR "\033[38;2;"
#define BACKGROUND_COLOR "\033[48;2;"
#define RESET "\033[m"

// BLACK to WHITE
#define BLACK "0;0;0m"
#define DIMGREY "105;105;105m"
#define GREY "128;128;128m"
#define DARKGREY "169;169;169m"
#define SILVER "192;192;192m"
#define LIGHTGREY "211;211;211m"
#define WHITE "255;255;255m"

// RED
#define LIGHTSALMON "255;160;122m"
#define SALMON "250;128;114m"
#define DARKSALMON "233;150;122m"
#define LIGHTPINK "255;192;203m"
#define PINK "255;182;193m"
#define HOTPINK "255;105;180m"
#define DARKPINK "255;20;147"
#define CRIMSON "220;20;60m"
#define RED "255;0;0m"
#define BROWN "165;42;42m"
#define MAROON "128;0;0m"
#define PALEVIOLETRED "219;112;147m"
#define MEDIUMVIOLETRED "199;21;133m"

// ORANGE AND YELLOW
#define CORAL "255;127;80m"
#define ORANGE "255;165;0m"
#define DARKORANGE "255;140;0m"
#define ORANGERED "255;69;0m"
#define LIGHTYELLOW "255;255;224m"
#define YELLOW "255;255;0m"
#define KHAKI "240;230;140m"
#define DARKKHAKI "189;183;107m"
#define OLIVE "128;128;0m"

// GREEN
#define GREENYELLOW "173;255;47m"
#define YELLOWGREEN "154;205;50m"
#define LAWNGREEN "124;252;0m"
#define LIME "0;255;0m"
#define LIMEGREEN "50;205;50m"
#define FORESTGREEN "34;139;34m"
#define GREEN "0;128;0m"
#define DARKGREEN "0;100;0m"
#define SPRINGGREEN "0,255,127m"
#define LIGHTGREEN "144;238;144m"
#define PALEGREEN "152;251;152m"
#define MEDIUMSEAGREEN "60;179;113m"
#define SEAGREEN "46;139;87m"
#define DARKSEAGREEN "143;188;143m"
#define DARKOLIVEGREEN "85;107;47m"
#define OLIVEDRAB "107;142;35m"

// BLUE
#define LIGHTBLUE "173;216;230m"
#define LIGHTSKYBLUE "135;206;250m"
#define SKYBLUE "135;206;235m"
#define DARKSKYBLUE "0;191;255m"
#define LIGHTSTEELBLUE "176;196;222m"
#define STEELBLUE "70;130;180m"
#define DODGERBLUE "30;144;255m"
#define CORNFLOWERBLUE "100;149;237m"
#define ROYALBLUE "65;105;225m"
#define BLUE "0;0;255m"
#define MEDIUMBLUE "0;0;205m"
#define DARKBLUE "0;0;139m"
#define NAVY "0;0;128m"
#define MIDNIGHTBLUE "25;25;112m"

// PURPLE
#define LAVENDER "230;230;250m"
#define THISTLE "216;191;216m"
#define PLUM "221;160;221m"
#define VIOLET "238;130;238m"
#define BLUEVIOLET "138;43;226m"
#define DARKVIOLET "148;0;211m"
#define ORCHID "218;112;214m"
#define MEDIUMORCHID "186;85;211m"
#define DARKORCHID "153;50;204m"
#define MAGENTA "255;0;255m"
#define DARKMAGENTA "139;0;139m"
#define MEDIUMPURPLE "147;112;219m"
#define PURPLE "128;0;128m"
#define INDIGO "75;0;130m"

void printColor(string str, string text, string background, bool reset)
{
    cout << TEXT_COLOR << text << BACKGROUND_COLOR << background << str;
    if (reset)
        cout << RESET;
}
void printColor(string str, string text, bool reset)
{
    cout << TEXT_COLOR << text << str;
    if (reset)
        cout << RESET;
}
void printColor(string str, string background, int whatever, bool reset)
{
    cout << BACKGROUND_COLOR << background << str;
    if (reset)
        cout << RESET;
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

void printStartBanner(int second)
{
    chrono::seconds last(second);
    chrono::duration<double, milli> pass(0), interval(15);
    int count = 0, strlen;
    string GO1 = "GO GO GO GO GO GO GO GO GO GO GO GO ";
    string GO2 = " GO GO GO GO GO GO GO GO GO GO GO GO";
    string PokemonGo = "   POCKET SHRINK!     ALABAMA YA!   ";
    strlen = GO1.length();
    string PokemonNames, playerName = "Alibuda", enemyName = "Alibaba";
    for (int i = 0; i < (strlen - 4 - playerName.length() - enemyName.length() + 1) / 2; i++)
        PokemonNames += ' ';
    PokemonNames += playerName + " vs " + enemyName;
    for (int i = 0; i < (strlen - 4 - playerName.length() - enemyName.length()) / 2; i++)
        PokemonNames += ' ';

    cout << "\0337" << flush;
    while (!(pass >= last && count % strlen == 1))
    {
        cout << "\0338\n\n\033[1m"
             << BACKGROUND_COLOR << CRIMSON << TEXT_COLOR << SALMON << stringMoving(GO1, count % strlen) << RESET << '\n'
             << BACKGROUND_COLOR << LIGHTYELLOW << setw(strlen) << ' ' << RESET << '\n'
             << BACKGROUND_COLOR << LIGHTYELLOW << "\033[1m" << stringMoving(PokemonNames, count % strlen) << RESET << '\n'
             << BACKGROUND_COLOR << LIGHTYELLOW << setw(strlen) << ' ' << RESET << '\n'
             << BACKGROUND_COLOR << LIGHTYELLOW << "\033[1m" << stringMoving(PokemonGo, count % strlen) << RESET << '\n'
             << BACKGROUND_COLOR << LIGHTYELLOW << setw(strlen) << ' ' << RESET << '\n'
             << BACKGROUND_COLOR << BLUE << TEXT_COLOR << BLUE << stringMoving(GO2, count % strlen) << RESET << "\n\n\n"
             << flush;
        this_thread::sleep_for(interval);
        pass += interval;
        count++;
        interval += chrono::duration<double, milli>(cbrt(2 * count) * 0.07);
    }
    return;
}

void printStartBannertest(int second)
{
    chrono::seconds last(second);
    chrono::milliseconds pass(0);
    int count = 0, strlen;
    cout << "\0337";
    while (pass < last)
    {
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "\0338" << count << '\n';
        cout << count * 10 << flush;
        pass += chrono::milliseconds(1000);

        count++;
    }
    return;
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
         << flush;
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
         << flush;
}

void printFallingWin()
{
    chrono::duration<double, milli> interval(15);
    this_thread::sleep_for(chrono::milliseconds(700));

    vector<string> YOU;
    YOU.push_back("      \\/_/    \\/_____/ \\/_____/  \n");
    YOU.push_back("     \\ \\_\\   \\ \\_____\\\\ \\_____\\ \n");
    YOU.push_back("   `\\ \\ \\   \\ \\ \\_\\ \\\\ \\ \\_\\ \\  \n");
    YOU.push_back(" `\\ `\\ /'  \\ \\ \\ \\ \\\\ \\ \\ \\ \\ \n");
    YOU.push_back("\\ `\\`\\\\/'/\\ \\ \\/\\ \\\\ \\ \\ \\ \\ \n");
    YOU.push_back("/\\ \\  /\\ \\/\\  __`\\ /\\ \\/\\ \\  \n");
    YOU.push_back(" __    __  _____    __  __   \n");
    cout << TEXT_COLOR << BLUE << "\033[1m";
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
    cout << TEXT_COLOR << RED << "\033[1m\033[7F";
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
void printFallingLose()
{
    // cout << "\033[7S\033[7F" << flush;
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
    cout << TEXT_COLOR << BLUE << "\033[1m";
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
    cout << TEXT_COLOR << RED << "\033[1m\033[7F";
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

int main()
{
    AudioFile<double> audiofile;
    audiofile.load("test-audio.wav");

    // string str = "viu -t -w 60 ./image/pikachu.png";
    // char *ch;
    // strcpy(ch, str.c_str());
    // system(ch);

    // int num = 2;
    // vector<int> v;
    // for (int i = 0; i < 4; i++)
    //     v.push_back(i);
    // for (int i = 0; i < v.size(); i++)
    //     cout << v[i] << ' ';
    // cout << endl;
    // random_device rd;
    // mt19937 f(rd());
    // shuffle(v.begin(), v.end(), f);
    // int popNum = v.size() - num;
    // for (int i = 0; i < popNum; i++)
    //     v.pop_back();
    // vector<int> t;
    // t.push_back(v[0]);
    // for (int i = 1; i < v.size(); i++)
    // {
    //     bool in = 0;
    //     for (int j = 0; j < t.size(); j++)
    //     {
    //         if (v[i] < t[j])
    //         {
    //             t.insert(t.begin() + j, v[i]);
    //             in = 1;
    //             break;
    //         }
    //     }
    //     if (!in)
    //         t.push_back(v[i]);
    // }
    // v = t;
    // for (int i = 0; i < v.size(); i++)
    //     cout << v[i] << ' ';
    // cout << endl;

    // cout << "\033[?25l";
    // cout << "\033[16S\033[15F" << flush;
    // printFallingWin();
    // this_thread::sleep_for(chrono::milliseconds(700));
    // printFallingLose();
    // cout << "\n\033[?25h";

    // for (int i = 0; i < 3; i++)
    // {
    //     printWin();
    //     this_thread::sleep_for(chrono::milliseconds(300));
    //     cout << "\033[7F\033[J" << flush;
    //     this_thread::sleep_for(chrono::milliseconds(300));
    // }
    // printWin();

    // cout << TEXT_COLOR << BROWN << "\033[1m";
    // cout << " __    __  _____    __  __      __      __   ______   __    __      __     \n"
    //      << "/\\ \\  /\\ \\/\\  __`\\ /\\ \\/\\ \\    /\\ \\  __/\\ \\ /\\__  _\\ /\\ \\_,/\\ \\    /\\ \\    \n"
    //      << "\\ `\\`\\\\/'/\\ \\ \\/\\ \\\\ \\ \\ \\ \\   \\ \\ \\/\\ \\ \\ \\\\/_/\\ \\/ \\ \\  _`\\` \\   \\ \\ \\   \n"
    //      << " `\\ `\\ /'  \\ \\ \\ \\ \\\\ \\ \\ \\ \\   \\ \\ \\ \\ \\ \\ \\  \\ \\ \\  \\ \\ \\,\\_  \\   \\ \\_\\  \n"
    //      << "   `\\ \\ \\   \\ \\ \\_\\ \\\\ \\ \\_\\ \\   \\ \\ \\_/ \\_\\ \\  \\_\\ \\__\\ \\ \\_ `\\ \\   \\/_/_ \n"
    //      << "     \\ \\_\\   \\ \\_____\\\\ \\_____\\   \\ `\\___x___/  /\\_____\\\\ \\_\\`\\ \\_\\    /\\_\\\n"
    //      << "      \\/_/    \\/_____/ \\/_____/    '\\/__//__/   \\/_____/ \\/_/  \\/_/    \\/_/\n"
    //      << flush;

    // cout << TEXT_COLOR << RED << "\033[1m";
    // cout << " __    __  _____    __  __      __        _____    ______    _______      __     \n"
    //      << "/\\ \\  /\\ \\/\\  __`\\ /\\ \\/\\ \\    /\\ \\      /\\  __`\\ /\\  ___`\\  /\\  ____\\   /\\ \\    \n"
    //      << "\\ `\\`\\\\/'/\\ \\ \\/\\ \\\\ \\ \\ \\ \\   \\ \\ \\     \\ \\ \\/\\ \\\\ \\,\\_L\\_\\\\ \\ \\___,/   \\ \\ \\   \n"
    //      << " `\\ `\\ /'  \\ \\ \\ \\ \\\\ \\ \\ \\ \\   \\ \\ \\     \\ \\ \\ \\ \\\\/_\\___ \\ \\ \\  ___\\    \\ \\_\\  \n"
    //      << "   `\\ \\ \\   \\ \\ \\_\\ \\\\ \\ \\_\\ \\   \\ \\ \\_____\\ \\ \\_\\ \\ /\\ \\_L\\ \\\\ \\ \\_,/___  \\/_/_ \n"
    //      << "     \\ \\_\\   \\ \\_____\\\\ \\_____\\   \\ \\_____`\\\\ \\_____\\\\ `\\_____\\\\ \\_______\\   /\\_\\\n"
    //      << "      \\/_/    \\/_____/ \\/_____/    \\/_____`/ \\/_____/ \\/______/ \\/_______/   \\/_/\n"
    //      << flush;

    // chrono::duration<double, milli> interval(100);
    // int count = 0, round = 1;
    // string str = " ROUND " + to_string(round) + " ";
    // int strlen = str.length();
    // for (int i = 0; i < strlen; i++)
    //     str.insert(str.begin(), ' ');
    // cout << "\0337";
    // while (count <= strlen)
    // {
    //     cout << "\0338\033[J\033[1m" << TEXT_COLOR << WHITE << BACKGROUND_COLOR << RED
    //          << stringMoving(str, count, strlen)
    //          << flush;
    //     this_thread::sleep_for(interval);
    //     count++;
    // }
    // cout << RESET << "\n\n"
    //      << "Choose your skill!\n\n";
    // this_thread::sleep_for(10 * interval);
    // system("\033[6n");

    // cout << "\033#3ok\n\033#4ok";

    // double random;
    // random_device rd;
    // mt19937 f(rd());
    // uniform_real_distribution<> dis(0.85, 1.0);
    // random = dis(f);
    // for (int i = 0; i < 10; i++)
    //     cout << dis(f) << ' ';

    // double in;
    // cin >> in;
    // cout << floor(in) << ' ' << ceil(in);

    // stringbuf sbuf(ios::out);
    // streambuf *oldbuf = cout.rdbuf(addressof(sbuf));
    // cout << "\033[6n";
    // cout.rdbuf(oldbuf);

    // string output = sbuf.str();
    // cout << output;
    // for (auto &c : output)
    // {
    //     // c = to_string(c);
    //     cout << to_string(c) << '\n';
    // }
    // cout << output;

    // char buffer[512];
    // string cmd = "ls";
    // string result;
    // FILE *pipe = popen(cmd.c_str(), "r");

    // while (!feof(pipe))
    //     if (fgets(buffer, sizeof(buffer), pipe) != NULL)
    //         result += buffer;

    // pclose(pipe);

    // cout << result;

    return 0;
} */