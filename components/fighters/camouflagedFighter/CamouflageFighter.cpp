#include "CamouflageFighter.h"

int CamouflageFighter::getDetectionRadius() {
    return detectionRadius * detectionCoef;
}