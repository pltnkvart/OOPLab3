#include "Echelon.h"

std::mutex bulletsMutex;

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
    std::cout << "Simulating air raid on echelon" << targetEchelon.getCommand() << std::endl;

    std::vector<std::thread> threads;

    int numThreads = std::min<int>(static_cast<int>(fighters.size()), std::thread::hardware_concurrency());

    int fightersPerThread = fighters.size() / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        int startIndex = i * fightersPerThread;
        int endIndex = (i == numThreads - 1) ? fighters.size() : (i + 1) * fightersPerThread;
        threads.emplace_back(&Echelon::simulateAirRaidThread, this, std::ref(targetEchelon), std::ref(bullets),
                             startIndex, endIndex);
    }

    for (auto &thread: threads) {
        thread.join();
    }
}


void Echelon::simulateAirRaidThread(const Echelon &targetEchelon, std::vector<Bullet> &bullets, int startIndex,
                                    int endIndex) {
    std::lock_guard<std::mutex> lock(bulletsMutex);
    auto it = fighters.begin();
    std::advance(it, startIndex);
    for (int i = startIndex; i < endIndex; ++i, ++it) {
        auto &attacker = *it;
        for (auto &targetFighter: targetEchelon.getFighters()) {
            if (!targetFighter->isDead() && !attacker->isDead()) {
                Vector3 start = {static_cast<float>(attacker->getCoordinates().first), 3.0f,
                                 static_cast<float>(attacker->getCoordinates().second)};
                Vector3 end = {static_cast<float>(targetFighter->getCoordinates().first), 3.0f,
                               static_cast<float>(targetFighter->getCoordinates().second)};
                Bullet bullet{start, end};
                if (attacker->attemptAttack(targetFighter, attacker->getMostPowerfulWeapon())) {
                    std::cout << "Fighter '" << targetFighter->getModel() << "' successfully attacked.\n" << std::endl;
                    bullet.success = true;
                } else {
                    std::cout << "Fighter '" << targetFighter->getModel() << "' missed the attack.\n" << std::endl;
                }
                bullets.push_back(bullet);
            }
        }
    }
}


bool Echelon::areAllFightersDead() const {
    for (const auto &fighter: fighters) {
        if (!fighter->isDead()) {
            return false;
        }
    }
    return true;
}