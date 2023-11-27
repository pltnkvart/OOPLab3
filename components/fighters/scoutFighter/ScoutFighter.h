#ifndef _SCOUTFIGHTER_H
#define _SCOUTFIGHTER_H

#include "../Fighter.h"

/* Истребитель-разведчик - это лёгкий слабовооружённый
 * истребитель, однако обладающий одновременно системами улучшенного радиообнаружения и маскировки, а также
 * хорошим радиусом обнаружения*/


class ScoutFighter : public Fighter {
private:
    int maskingIgnoreCoef;
    int hitCoef;
    int detectionCoef;
public:
    int getDetectionRadius() override;

    int getAttackRadius() override {
        // Реализация для истребителя
        return 1;
    }


    bool attemptAttack(Fighter *target) override {
        // Реализация для истребителя
        return true;
    }
};

#endif //_SCOUTFIGHTER_H