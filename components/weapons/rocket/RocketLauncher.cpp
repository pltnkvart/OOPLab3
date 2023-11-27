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
