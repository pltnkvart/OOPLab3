#include "REBFighter.h"


bool REBFighter::attemptAttack(Fighter *target, Weapon *weapon) {
    if (weapon->getWeaponAttackRadius() >= target->getDetectionRadius() * suppressionCoef) {
        std::srand(std::time(nullptr));
        int chance = std::rand() % 100;
        Projectile prj = weapon->fire();
        if (prj.getHitRate() * suppressionCoef > chance) {
            target->getDamage(prj);
            return true;
        }
    }
    return false;
}
