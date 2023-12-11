#include "Echelon.h"

void Echelon::addFighter(std::unique_ptr<Fighter> fighter) {
    fighters.push_back(std::move(fighter));
}

Fighter Echelon::removeFighter(int number) {
    if (number < 0 || number >= getNumFighters()) {
        throw std::out_of_range("Invalid fighter number");
    }
    auto it = std::next(fighters.begin(), number);
    Fighter removedFighter = std::move(**it);
    fighters.erase(it);
    return removedFighter;
}

int Echelon::getEchelonDetectionRadius() {
    if (fighters.empty()) {
        return 0;
    }
    auto maxDetectionRadiusFighter = std::max_element(
            fighters.begin(), fighters.end(),
            [](const std::unique_ptr<Fighter> &a, const std::unique_ptr<Fighter> &b) {
                return a->detectionRadius < b->detectionRadius;
            });
    return (*maxDetectionRadiusFighter)->detectionRadius;
}
