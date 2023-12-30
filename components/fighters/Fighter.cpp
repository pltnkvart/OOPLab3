#include "Fighter.h"

int Fighter::getAttackRadius() {
    if (equipment.empty()) {
        throw std::runtime_error("Equipment list is empty.");
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

bool Fighter::attemptAttack(std::shared_ptr<Fighter> target, std::shared_ptr<Weapon> weapon) {
//    std::cout << this->getModel() << " is attacking " << target->getModel() << std::endl;
//    std::cout << "before shot - " << target->getHP() << std::endl;

    if (weapon->getWeaponAttackRadius() >= target->getDetectionRadius()) {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 gen(static_cast<unsigned>(seed));
        std::uniform_int_distribution<int> distribution(0, 100);
        int chance = distribution(gen);
        Projectile prj = weapon->fire();
//        std::cout << "hit rate - " << prj.getHitRate() << " chance - " << chance << std::endl;
        if (prj.getHitRate() > chance) {
            target->getDamage(prj);
//            std::cout << "after shot - " << target->getHP() << std::endl;
            return true;
        }
//        std::cout << "after shot - " << target->getHP() << std::endl;
    }
    return false;
}

std::shared_ptr<Weapon> Fighter::getMostPowerfulWeapon() const {
    auto maxDamageWeapon = std::max_element(equipment.begin(), equipment.end(),
                                            [](const std::shared_ptr<Weapon> &weapon1,
                                               const std::shared_ptr<Weapon> &weapon2) {
                                                return weapon1->getDamageOfWeapon() < weapon2->getDamageOfWeapon();
                                            });
    return *maxDamageWeapon;
}