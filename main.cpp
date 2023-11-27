#include <iostream>
#include "components/fighters/Fighter.h"
#include "components/fighters/camouflagedFighter/CamouflageFighter.h"
#include "components/fighters/scoutFighter/ScoutFighter.h"
#include "components/weapons/gun/gun.h"

int main() {
    std::vector<Weapon *> weapons;
    Gun weapon1("gun1", 30, 15, 5, 70);
    weapons.push_back(&weapon1);

    Fighter Fighter1("f1", 150, 10, 1, weapons, std::pair<int, int> (1, 1), 5);
    Fighter Fighter2("f2", 150, 10, 1, weapons, std::pair<int, int> (1, 1), 10);

    Fighter1.attemptAttack(&Fighter2);

    return 0;
}