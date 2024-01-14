#include <string>
#include <vector>
#include <memory>
#include "attribute.h"
#include "color.h"
using namespace std;

vector<shared_ptr<Attribute> /**/> attributeList;

void setAttributes()
{
    shared_ptr<Attribute> none = make_shared<Attribute>();
    shared_ptr<Attribute> water = make_shared<Attribute>("water");
    shared_ptr<Attribute> fire = make_shared<Attribute>("fire");
    shared_ptr<Attribute> grass = make_shared<Attribute>("grass");
    shared_ptr<Attribute> normal = make_shared<Attribute>("normal");
    shared_ptr<Attribute> mad = make_shared<Attribute>("mad");
    attributeList.push_back(none);
    attributeList.push_back(water);
    attributeList.push_back(fire);
    attributeList.push_back(grass);
    attributeList.push_back(normal);
    attributeList.push_back(mad);
}

Attribute::Attribute()
{
    water = 0;
    fire = 0;
    grass = 0;
    normal = 0;
    mad = 0;
}

Attribute::Attribute(string str)
{
    water = 0;
    fire = 0;
    grass = 0;
    normal = 0;
    mad = 0;
    if (str.compare("water") == 0)
        water = 1;
    else if (str.compare("fire") == 0)
        fire = 1;
    else if (str.compare("grass") == 0)
        grass = 1;
    else if (str.compare("normal") == 0)
        normal = 1;
    else if (str.compare("mad") == 0)
        mad = 1;
}

double Attribute::attributeEffect(shared_ptr<Attribute> rivalAtr)
{
    if (water)
    {
        if (rivalAtr->fire)
            return 2.0;
        if (rivalAtr->grass)
            return 0.5;
        return 1;
    }
    if (fire)
    {
        if (rivalAtr->grass)
            return 2.0;
        if (rivalAtr->water)
            return 0.5;
        return 1;
    }
    if (grass)
    {
        if (rivalAtr->water)
            return 2.0;
        if (rivalAtr->fire)
            return 0.5;
        return 1;
    }
    return 1;
}

void Attribute::atrPrintColor(bool isBold)
{
    if (water)
    {
        cout << BACKGROUND_COLOR << BLUE
             << TEXT_COLOR << WHITE;
    }
    else if (fire)
    {
        cout << BACKGROUND_COLOR << RED
             << TEXT_COLOR << WHITE;
    }
    else if (grass)
    {
        cout << BACKGROUND_COLOR << FORESTGREEN
             << TEXT_COLOR << WHITE;
    }
    else if (normal)
    {
        cout << BACKGROUND_COLOR << DARKGREY
             << TEXT_COLOR << WHITE;
    }
    else if (mad)
    {
        cout << BACKGROUND_COLOR << MAGENTA
             << TEXT_COLOR << WHITE;
    }
    else
    {
        cout << BACKGROUND_COLOR << LIGHTYELLOW
             << TEXT_COLOR << BLACK;
    }
    if (isBold)
        cout << "\033[1m";
}

shared_ptr<Attribute> Attribute::getProAttribute()
{
    if (this->getName() == "water")
        return attributeList[2];
    if (this->getName() == "fire")
        return attributeList[3];
    if (this->getName() == "grass")
        return attributeList[1];
    if (this->getName() == "normal")
        return attributeList[5];
    if (this->getName() == "mad")
        return attributeList[4];
    return attributeList[0];
}

/* Attribute::Attribute(Attribute &atr)
{
    water = atr.water;
    fire = atr.fire;
    grass = atr.grass;
    normal = atr.normal;
    mad = atr.mad;
} */

string Attribute::getName()
{
    if (water)
        return "water";
    else if (fire)
        return "fire";
    else if (grass)
        return "grass";
    else if (normal)
        return "normal";
    else if (mad)
        return "mad";
    return "none";
}
