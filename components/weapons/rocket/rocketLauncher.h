#ifndef _ROCKETLAUNCHER_H
#define _ROCKETLAUNCHER_H

#include "../Weapon.h"

class RocketLauncher : public Weapon {
private:
    int maxAmmo;
    int currAmmo;
public:
    RocketLauncher(std::string, int dmg, int attackRad, int shootingS ,int currAmmo, int maxAmmo);

    [[nodiscard]] int getMaxAmmo() const { return maxAmmo; };

    void setMaxAmmo(int value) { maxAmmo = value; };

    [[nodiscard]] int getCurrAmmo() const { return currAmmo; };

    void setCurrAmmo(int value) { currAmmo = value; };

    Projectile fire() override;

    bool isOperational() override;
};

#endif //_ROCKETLAUNCHER_H