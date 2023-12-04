#ifndef _REBFIGHTER_H
#define _REBFIGHTER_H

#include "../Fighter.h"

/* Система РЭБ позволяет на определённый коэффициент уменьшить в целом эффективность работы вражеских
 * радиоэлектронных систем в определённом радиусе, уменьшая вероятность срабатывания ПРО, а также
 * эффективность систем маскировки и радиообнаружения.
 * */

class REBFighter : public Fighter {
private:
    int suppressionCoef; // < 1
public:
    bool attemptAttack(Fighter *target, Weapon *weapon) override;
};

#endif //_REBFIGHTER_H