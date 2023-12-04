#include "PROFighter.h"

void PROFighter::getDamage(Projectile prj) {
    std::srand(std::time(nullptr));
    int chance = std::rand() % 100;
    if (prj.getWeaponType() == WeaponType::ROCKET && numberOfCharges > 0 && chanceWorking > chance) {
        numberOfCharges--;
    } else {
        HP -= prj.getProjectileDamage();
    }
}
