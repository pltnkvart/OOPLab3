#ifndef _ECHELON_H
#define _ECHELON_H

#include "../fighters/Fighter.h"
#include <iostream>
#include <list>

class Echelon {
private:
    std::list<Fighter *> fighters;
    std::string command;
    std::pair<int, int> coordinates;
public:
    bool addFighter(Fighter fighter);

    Fighter removeFighter(int number);

    int getDetectionRadius();

    int getStealth();

    [[nodiscard]] int getNumFighters() const { return static_cast<int>(fighters.size()); }
};

#endif //_ECHELON_H