#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "weaponType.h"

class Projectile {
private:
    int damage;
    int hitRate;
    WeaponType type;
public:
    Projectile(int dmg, int rate, WeaponType _type) {
        damage = dmg;
        hitRate = rate;
        type = _type;
    }

    [[nodiscard]] int getProjectileDamage() const { return damage; }

    [[nodiscard]] int getHitRate() const { return hitRate; }
};

#endif //_PROJECTILE_H