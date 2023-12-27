#include "Echelon.h"

void Echelon::addFighter(std::shared_ptr<Fighter> fighter) {
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

int Echelon::getEchelonDetectionRadius() const {
    if (fighters.empty()) {
        return 0;
    }
    auto maxDetectionRadiusFighter = std::max_element(
            fighters.begin(), fighters.end(),
            [](const std::shared_ptr<Fighter> &a, const std::shared_ptr<Fighter> &b) {
                return a->detectionRadius < b->detectionRadius;
            });
    return (*maxDetectionRadiusFighter)->detectionRadius;
}


const std::list<std::shared_ptr<Fighter>> &Echelon::getFighters() const {
    return fighters;
}

void Echelon::simulateAirRaid(const Echelon &targetEchelon, std::vector<Bullet> &bullets) {
    std::cout << "Simulating air raid on echelon '" << targetEchelon.getCommand() << "' at coordinates ("
              << targetEchelon.getCoordinates().first << ", " << targetEchelon.getCoordinates().second << ")."
              << std::endl;

    for (auto &attacker: fighters) {
        for (auto &targetFighter: targetEchelon.getFighters()) {
            if (!targetFighter->isDead() && !attacker->isDead()) {
                Vector3 start = {static_cast<float>(attacker->getCoordinates().first), 3.0f,
                                 static_cast<float>(attacker->getCoordinates().second)};
                Vector3 end = {static_cast<float>(targetFighter->getCoordinates().first), 3.0f,
                               static_cast<float>(targetFighter->getCoordinates().second)};
                Bullet bullet{start, end};
                if (attacker->attemptAttack(targetFighter, attacker->getMostPowerfulWeapon())) {
                    std::cout << "Fighter '" << targetFighter->getModel() << "' successfully attacked.\n" << std::endl;
                    bullet.success = 1;
                } else {
                    std::cout << "Fighter '" << targetFighter->getModel() << "' missed the attack.\n" << std::endl;
                }
                bullets.push_back(bullet);
            }
        }
    }
}

bool Echelon::areAllFightersDead() const {
    for (const auto& fighter : fighters) {
        if (!fighter->isDead()) {
            return false;
        }
    }
    return true;
}