#include "CamouflageFighter.h"

int CamouflageFighter::getDetectionRadius() {
    return detectionRadius * detectionCoef;
}

bool CamouflageFighter::attemptAttack(std::shared_ptr<Fighter> target, std::shared_ptr<Weapon> weapon) {
    if (weapon->getWeaponAttackRadius() >= target->getDetectionRadius()) {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 gen(static_cast<unsigned>(seed));
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
