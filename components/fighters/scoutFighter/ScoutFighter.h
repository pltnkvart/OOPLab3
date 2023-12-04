#ifndef _SCOUTFIGHTER_H
#define _SCOUTFIGHTER_H

#include "../Fighter.h"

/* Истребитель-разведчик - это лёгкий слабовооружённый
 * истребитель, однако обладающий одновременно системами улучшенного радиообнаружения и маскировки, а также
 * хорошим радиусом обнаружения*/


class ScoutFighter : public Fighter {
private:
    int maskingIgnoreCoef;
    int hitGunCoef;
    int detectionCoef;
public:
    int getDetectionRadius() override;

    bool attemptAttack(Fighter *target, Weapon *weapon) override;
};

#endif //_SCOUTFIGHTER_H