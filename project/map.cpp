#include <iostream>
#include <fstream>
#include <vector>
#include "map.h"
#include "Pokemonlist.h"
#include "color.h"
using namespace std;

vector<vector<int> /**/> map(MAP_X, vector<int>(MAP_Y, 0));

void setMap(ifstream &inmap)
{
    int c = 1;
    char *a = new char[3];
    for (int j = 0; j < MAP_Y; j++)
    {
        for (int i = 0; i < MAP_X; i++)
        {
            for (int t = 0; t < 3; t++)
                a[t] = inmap.get();
            if (a[0] == '[')
                map[i][j] = 5;
            else if (a[0] != ' ')
                map[i][j] = 3;
            else if (a[1] != ' ')
            {
                if (a[1] == '@')
                {
                    map[i][j] = 1;
                    Pos[c][0] = i;
                    Pos[c][1] = j;
                    c++;
                }
                else if (a[1] == '|')
                    map[i][j] = 4;
                else
                {
                    map[i][j] = 2;
                    Pos[0][0] = i;
                    Pos[0][1] = j;
                    inmap.get();
                    inmap.get();
                }
            }
        }
        inmap.ignore();
    }
    delete[] a;
    a = nullptr;
    return;
}

void printMap(vector<int> pos)
{
    cout << "\0338\0337\033[J\n";
    for (int i = 3 * (pos[0] - PRINT_RANGE - 1); i <= 3 * (pos[0] + PRINT_RANGE + 1); i++)
    {
        if (i % 5 == 0)
            printColor("*", SALMON, BROWN, 1);
        else
            printColor(" ", BROWN, 4, 1);
    }
    cout << '\n';
    for (int j = (pos[1] - PRINT_RANGE); j < (pos[1] + PRINT_RANGE + 1); j++)
    {
        if ((j + PRINT_RANGE) % 3 == 1)
            printColor("* ", SALMON, BROWN, 1);
        else if ((j + PRINT_RANGE) % 3 == 2)
            printColor(" *", SALMON, BROWN, 1);
        else
            printColor("  ", SALMON, BROWN, 1);
        // cout << ' ';
        for (int i = (pos[0] - PRINT_RANGE); i < (pos[0] + PRINT_RANGE + 1); i++)
        {
            if (i >= 0 && i < MAP_X && j >= 0 && j < MAP_Y)
            {
                if (i == pos[0] && j == pos[1])
                    printColor(" ▼ ", FORESTGREEN, 1);
                else if (map[i][j] == 0)
                    cout << "   ";
                else if (map[i][j] == 1)
                    printColor(" @ ", BLUE, 1);
                else if (map[i][j] == 2)
                    printColor(" ▼ ", FORESTGREEN, 1);
                else if (map[i][j] == 3)
                    printColor("-- ", DARKGREY, DIMGREY, 1);
                else if (map[i][j] == 4)
                    printColor(" | ", DARKGREY, DIMGREY, 1);
                else if (map[i][j] == 5)
                    printColor("   ", DIMGREY, 4, 1);
                else if (map[i][j] == 6)
                    printColor("_†_", WHITE, SILVER, 1);
            }
            else
                cout << "   ";
        }
        // cout << ' ';
        if ((j + PRINT_RANGE) % 3 == 2)
            printColor("* ", SALMON, MAROON, 1);
        else if ((j + PRINT_RANGE) % 3 == 0)
            printColor(" *", SALMON, MAROON, 1);
        else
            printColor("  ", SALMON, MAROON, 1);
        cout << '\n';
    }
    for (int i = 3 * (pos[0] - PRINT_RANGE - 1); i <= 3 * (pos[0] + PRINT_RANGE + 1); i++)
    {
        if ((i + 2) % 5 == 0)
            printColor("*", SALMON, MAROON, 1);
        else
            printColor(" ", MAROON, 4, 1);
    }
    cout << "\n\n"
         << flush;
    return;
}