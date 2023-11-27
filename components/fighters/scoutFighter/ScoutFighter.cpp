#include "ScoutFighter.h"

int ScoutFighter::getDetectionRadius() {
    return detectionRadius * detectionCoef;
}