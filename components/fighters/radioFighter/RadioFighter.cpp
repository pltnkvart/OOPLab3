#include "RadioFighter.h"


bool RadioFighter::attemptAttack(Fighter *target, Weapon *weapon) {
    if (weapon->getWeaponAttackRadius() >= target->getDetectionRadius() * maskingIgnoreCoef) {
        std::srand(std::time(nullptr));
        int chance = std::rand() % 100;
        Projectile prj = weapon->fire();
        if (prj.getHitRate() > chance) {
            target->getDamage(prj);
            return true;
        }
    }
    return false;
}
