#include "rocketLauncher.h"

Projectile RocketLauncher::fire() {
    if (isOperational()) {
        currAmmo--;
        return {getDamageOfWeapon(), 100, WeaponType::ROCKET};
    } else {
        return {0, 0, WeaponType::NONE};
    }
}

bool RocketLauncher::isOperational() {
    return currAmmo != 0 && maxAmmo > 0;
}

RocketLauncher::RocketLauncher(std::string _name, int _dmg, int _attackRad, int _shootingS, int _currAmmo, int _maxAmmo) {
    name = _name;
    damage = _dmg;
    attackRadius = _attackRad;
    shootingSpeed = _shootingS;
    currAmmo = _currAmmo;
    maxAmmo = _maxAmmo;
}
