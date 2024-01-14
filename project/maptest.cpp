/*#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAP_X = 19;
const int MAP_Y = 19;
string **map = new string *[MAP_X];

void setMap(ifstream &inmap);
void printMap(vector<int>pos);

int main()
{
    ifstream inmap("map.txt");
    if (inmap)
    {
        setMap(inmap);
        inmap.close();
    }
    vector<int>a = new int[2];
    a[0] = 0, a[1] = 0;
    printMap(a);

    return 0;
}

void setMap(ifstream &inmap)
{
    char *a = new char[3];
    for (int i = 0; i < MAP_X; i++)
        map[i] = new string[MAP_Y];
    for (int j = 0; j < MAP_Y; j++)
    {
        for (int i = 0; i < MAP_X; i++)
        {
            for (int t = 0; t < 3; t++)
            {
                a[t] = inmap.get();
                map[i][j] += a[t];
            }
        }
        inmap.ignore(100, '\n');
    }
    return;
}

void printMap(vector<int>pos)
{
    for (int j = 0; j < MAP_Y; j++)
    {
        for (int i = 0; i < MAP_X; i++)
        {
            cout << map[i][j];
        }
        cout << '\n';
    }
    return;
}*/
