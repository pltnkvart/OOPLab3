#ifndef _WEAPON_H
#define _WEAPON_H

#include <iostream>
#include "projectile.h"

class Weapon {
public:
    int damage;
    int attackRadius;
    int shootingSpeed;
    std::string name;
    WeaponType type;
public:
    [[nodiscard]] std::string getName() const { return name; };

    void setName(std::string value) { name = value; };

    [[nodiscard]] int getDamageOfWeapon() const { return damage; };

    void setDamage(int value) { damage = value; };

    [[nodiscard]] int getWeaponAttackRadius() const { return attackRadius; };

    void setWeaponAttackRadius(int value) { attackRadius = value; };

    [[nodiscard]] int getShootingSpeed() const { return shootingSpeed; };

    void setShootingSpeed(int value) { shootingSpeed = value; };

    virtual Projectile fire() = 0;

    virtual bool isOperational() = 0;
};

#endif //_WEAPON_H