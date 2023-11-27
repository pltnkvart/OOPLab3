#ifndef _FIGHTER_H
#define _FIGHTER_H

#include <iostream>
#include <list>
#include <memory>
#include "../weapons/Weapon.h"

class Fighter {
public:
    std::string model;
    int HP;
    int maxHP;
    int speed;
    int maxNumEquipment;
    std::vector<Weapon *> equipment;
    std::pair<int, int> coordinates;
    int detectionRadius;
public:
    Fighter(std::string _model, int _maxHP, int speed, int maxNumEquipment, std::vector<Weapon *> equipment,
            std::pair<int, int> coordinates, int detectionRadius);

    [[nodiscard]] std::string getModel() const { return model; };

    void setModel(std::string value) { model = value; };

    [[nodiscard]] int getHP() const { return HP; };

    void setHP(int value) { HP = value; };

    [[nodiscard]] int getMaxHP() const { return maxHP; };

    void setMaxSurvivability(int value) { maxHP = value; };

    [[nodiscard]] int getSpeed() const { return speed; };

    void setSpeed(int value) { speed = value; };

    [[nodiscard]] int getMaxNumEquipment() const { return maxNumEquipment; };

    void setMaxNumEquipment(int value) { maxNumEquipment = value; };

    [[nodiscard]] std::vector<Weapon *> getEquipment() const { return equipment; }

    void setEquipment(const std::vector<Weapon *> &value) { equipment = value; };

    [[nodiscard]] std::pair<int, int> getCoordinates() const { return coordinates; };

    void setCoordinates(std::pair<int, int> value) { coordinates = value; };

    void setDetectionRadius(int value) { detectionRadius = value; };

    virtual void getDamage(Projectile prg);

    virtual int getAttackRadius();

    virtual int getDetectionRadius();

    virtual bool attemptAttack(Fighter *target);

    virtual ~Fighter() = default;
};

#endif //_FIGHTER_H