#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "attribute.h"
using namespace std;

const int ATTRIBUTE_NUM = 6;

void setAttributes();

class Attribute
{
private:
    bool water;
    bool fire;
    bool grass;
    bool normal;
    bool mad;

public:
    Attribute();
    Attribute(string str);
    // Attribute(Attribute &atr);
    double attributeEffect(shared_ptr<Attribute> rivalAtr);
    void atrPrintColor(bool isBold);
    shared_ptr<Attribute> getProAttribute();
    string getName();
};

extern vector<shared_ptr<Attribute> /**/> attributeList;
