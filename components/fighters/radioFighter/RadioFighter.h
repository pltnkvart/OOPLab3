#ifndef _RADIOFIGHTER_H
#define _RADIOFIGHTER_H

#include "../Fighter.h"


/* Улучшенное радиообнаружение позволяет уменьшить на определённый коэффициент
 * влияние вражеской системы маскировки на радиус обнаружения (но не на вероятность попадания). */


class RadioFighter : public Fighter {
private:
    int maskingIgnoreCoef;
public:
    bool attemptAttack(Fighter *target, Weapon *weapon) override;
};

#endif //_RADIOFIGHTER_H