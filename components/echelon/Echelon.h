#ifndef _ECHELON_H
#define _ECHELON_H

#include "../fighters/Fighter.h"
#include <iostream>
#include <list>
#include "../../game/bullets/bullet.h"

class Echelon {
private:
    std::list<std::shared_ptr<Fighter>> fighters;
    std::string command;
    std::pair<int, int> coordinates;
public:
    void addFighter(std::shared_ptr<Fighter> fighter);

    Fighter removeFighter(int number);

    [[nodiscard]] int getEchelonDetectionRadius() const;

    [[nodiscard]] std::pair<int, int> getCoordinates() const { return coordinates; };

    [[nodiscard]] std::string getCommand() const { return command; };

    [[nodiscard]] const std::list<std::shared_ptr<Fighter>> &getFighters() const;

    [[nodiscard]] int getNumFighters() const { return static_cast<int>(fighters.size()); }

    void simulateAirRaid(const Echelon &targetEchelon, std::vector<Bullet> &bullets);

    bool areAllFightersDead() const;
};

#endif //_ECHELON_H