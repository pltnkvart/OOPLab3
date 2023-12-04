#include "ScoutFighter.h"

int ScoutFighter::getDetectionRadius() {
    return detectionRadius * detectionCoef;
}

bool ScoutFighter::attemptAttack(Fighter *target, Weapon *weapon) {
    if (weapon->getWeaponAttackRadius() >= target->getDetectionRadius() * maskingIgnoreCoef) {
        std::srand(std::time(nullptr));
        int chance = std::rand() % 100;
        Projectile prj = weapon->fire();
        if (weapon->getWeaponType() == WeaponType::GUN) {
            int newHitRateWithCoef = prj.getHitRate() * this->hitGunCoef;
            prj.setHitRate(newHitRateWithCoef);
        }
        if (prj.getHitRate() > chance) {
            target->getDamage(prj);
            return true;
        }
    }
    return false;
}
