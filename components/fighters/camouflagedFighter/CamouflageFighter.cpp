#include "CamouflageFighter.h"

int CamouflageFighter::getDetectionRadius() {
    return detectionRadius * detectionCoef;
}

bool CamouflageFighter::attemptAttack(Fighter *target, Weapon *weapon) {
    if (weapon->getWeaponAttackRadius() >= target->getDetectionRadius()) {
        std::mt19937 gen(std::time(nullptr));
        std::uniform_int_distribution<int> distribution(0, 100);
        int chance = distribution(gen);
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
