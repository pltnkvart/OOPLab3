#ifndef _CAMOUFLAGEFIGHTER_H
#define _CAMOUFLAGEFIGHTER_H

#include "../Fighter.h"

/*
 * Система маскировки позволяет увеличить вероятность промаха при стрельбе из пушки
 * а также уменьшить радиус обнаружения для данного истребителя (но не для всего звена в целом,
 * так как успешность сокрытия зависит от сокрытия наименее эффективного истребителя в крыле).
 */

class CamouflageFighter : public Fighter {
private:
    int hitRocketCoef;
    int detectionCoef; // < 1
public:
    int getDetectionRadius() override;
};


#endif //_CAMOUFLAGEFIGHTER_H