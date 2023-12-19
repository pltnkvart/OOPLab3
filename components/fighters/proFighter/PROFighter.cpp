#include "PROFighter.h"

void PROFighter::getDamage(Projectile prj) {
    std::mt19937 gen(std::time(nullptr));
    std::uniform_int_distribution<int> distribution(0, 100);
    int chance = distribution(gen);
    if (prj.getWeaponType() == WeaponType::ROCKET && numberOfCharges > 0 && chanceWorking > chance) {
        numberOfCharges--;
    } else {
        HP -= prj.getProjectileDamage();
    }
}
