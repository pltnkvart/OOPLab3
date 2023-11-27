#ifndef _PROFIGHTER_H
#define _PROFIGHTER_H

#include "../Fighter.h"

/* ПРО имеет несколько зарядов, позволяющих при использовании
 * с высокой вероятностью избежать попадания ракеты. */

class PROFighter : public Fighter {
private:
    int numberOfCharges;
    int maxNumberOfCharges;
public:
};

#endif //_PROFIGHTER_H