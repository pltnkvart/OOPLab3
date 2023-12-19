#include "RadioFighter.h"


bool RadioFighter::attemptAttack(Fighter *target, Weapon *weapon) {
    if (weapon->getWeaponAttackRadius() >= target->getDetectionRadius() * maskingIgnoreCoef) {
        std::mt19937 gen(std::time(nullptr));
        std::uniform_int_distribution<int> distribution(0, 100);
        int chance = distribution(gen);
        Projectile prj = weapon->fire();
        if (prj.getHitRate() > chance) {
            target->getDamage(prj);
            return true;
        }
    }
    return false;
}
