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
        std::srand(std::time(nullptr));
        int chance = std::rand() % 100;
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

Fighter::Fighter(std::string
                 _model, int
                 _maxHP, int
                 _speed, int
                 _maxNumEquipment, std::vector<Weapon *>
                 _equipment,
                 std::pair<int, int>
                 _coordinates, int
                 _detectionRadius) {
    model = _model;
    HP = _maxHP;
    maxHP = _maxHP;
    speed = _speed;
    maxNumEquipment = _maxNumEquipment;
    equipment = std::move(_equipment);
    coordinates = _coordinates;
    detectionRadius = _detectionRadius;
}
