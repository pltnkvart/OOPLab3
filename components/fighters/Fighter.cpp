#include "Fighter.h"

int Fighter::getAttackRadius() {
    if (equipment.empty()) {
        std::cerr << "Equipment list is empty." << std::endl;
        return -1;
    }
    auto maxRadiusWeapon = equipment.begin();
    for (auto it = equipment.begin(); it != equipment.end(); ++it) {
        if ((*it)->isOperational()) {
            if ((*it)->getWeaponAttackRadius() > (*maxRadiusWeapon)->getWeaponAttackRadius()) {
                maxRadiusWeapon = it;
            }
        }
    }
    return (*maxRadiusWeapon)->getWeaponAttackRadius();
}

int Fighter::getDetectionRadius() {
    return detectionRadius;
}

void Fighter::getDamage(Projectile projectile) {
    HP -= projectile.getProjectileDamage();
}

bool Fighter::attemptAttack(Fighter *target, Weapon *weapon) {
    std::cout << "before shot - " << target->getHP() << std::endl;

    if (weapon->getWeaponAttackRadius() >= target->getDetectionRadius()) {
        std::mt19937 gen(std::time(nullptr));
        std::uniform_int_distribution<int> distribution(0, 100);
        int chance = distribution(gen);
        Projectile prj = weapon->fire();

        std::cout << "hit rate - " << prj.getHitRate() << " chance - " << chance << std::endl;

        if (prj.getHitRate() > chance) {
            target->getDamage(prj);

            std::cout << "after shot - " << target->getHP() << std::endl;

            return true;
        }
    }
    return false;
}