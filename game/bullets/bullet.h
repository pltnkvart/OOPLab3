#ifndef LAB3_BULLET_H
#define LAB3_BULLET_H

#include <raylib.h>

class Bullet {
public:
    Vector3 position;
    Vector3 target;
    bool isActive;
    bool success;
public:
    Bullet(Vector3 startPos, Vector3 targetPos) : position(startPos), target(targetPos), isActive(true), success(false) {};
};

#endif //LAB3_BULLET_H
