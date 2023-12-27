#include "PROFighter.h"

void PROFighter::getDamage(Projectile prj) {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(static_cast<unsigned>(seed));
    std::uniform_int_distribution<int> distribution(0, 100);
    int chance = distribution(gen);
    if (prj.getWeaponType() == WeaponType::ROCKET && numberOfCharges > 0 && chanceWorking > chance) {
        numberOfCharges--;
    } else {
        HP -= prj.getProjectileDamage();
    }
}
