#ifndef _REBFIGHTER_H
#define _REBFIGHTER_H

#include "../Fighter.h"

/* Система РЭБ позволяет на определённый коэффициент уменьшить в целом эффективность работы вражеских
 * радиоэлектронных систем в определённом радиусе, уменьшая вероятность срабатывания ПРО, а также
 * эффективность систем маскировки и радиообнаружения.
 * */

class REBFighter : public Fighter {
private:
    int suppressionCoef;
public:
    int getAttackRadius() override {
        // Реализация для истребителя
        return 50;
    }

    bool attemptAttack(Fighter *target) override {
        // Реализация для истребителя
        return true;
    }
};

#endif //_REBFIGHTER_H