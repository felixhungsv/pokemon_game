#pragma once
#include <iostream>
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
#define INDIANRED "205;92;92m"
#define CRIMSON "220;20;60m"
#define FIREBRICK "178;34;34m"
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
#define PURPLR "128;0;128m"
#define INDIGO "75;0;130m"

void printColor(string str, string text, string background, bool reset);
void printColor(string str, string text, bool reset);
void printColor(string str, string background, int whatever, bool reset);
