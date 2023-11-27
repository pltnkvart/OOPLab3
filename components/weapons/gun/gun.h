#ifndef _GUN_H
#define _GUN_H

#include "../Weapon.h"
#include "../projectile.h"

class Gun : public Weapon {
private:
    int hitPercentage;
public:
    Gun(std::string, int dmg, int attackRad, int shootingSpeed, int hitPer);

    [[nodiscard]] int getHitPercentage() const { return hitPercentage; };

    void setHitPercentage(int value) { hitPercentage = value; };

    Projectile fire() override;

    bool isOperational() override;
};

#endif //_GUN_H