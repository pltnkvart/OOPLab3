#include "CamouflageFighter.h"

int CamouflageFighter::getDetectionRadius() {
    return detectionRadius * detectionCoef;
}

bool CamouflageFighter::attemptAttack(Fighter *target, Weapon *weapon) {
    if (weapon->getWeaponAttackRadius() >= target->getDetectionRadius()) {
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
