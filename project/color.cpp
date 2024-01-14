#include <iostream>
#include "color.h"
using namespace std;

void printColor(string str, string text, string background, bool reset)
{
    cout << TEXT_COLOR << text
         << BACKGROUND_COLOR << background << str;
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
