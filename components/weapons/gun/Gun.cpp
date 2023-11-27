#include "gun.h"

Projectile Gun::fire() {
    if (isOperational()) {
        return {getDamageOfWeapon(), hitPercentage, WeaponType::GUN};
    } else {
        return {0, 0, WeaponType::NONE};
    }
}

bool Gun::isOperational() {
    return getShootingSpeed() > 0;
}

Gun::Gun(std::string _name, int _dmg, int _attackRad, int _shootingSpeed, int _hitPer) {
    name = _name;
    damage = _dmg;
    attackRadius = _attackRad;
    shootingSpeed = _shootingSpeed;
    hitPercentage = _hitPer;
}
