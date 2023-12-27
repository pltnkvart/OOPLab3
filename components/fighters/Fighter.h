#ifndef _FIGHTER_H
#define _FIGHTER_H

#include <iostream>
#include <list>
#include <memory>
#include <random>
#include <utility>
#include "../weapons/Weapon.h"

/**
 * @brief Класс истребителя
 */
class Fighter {
public:
    std::string model;
    int HP;
    int maxHP;
    int speed;
    int maxNumEquipment;
    std::vector<std::shared_ptr<Weapon>> equipment;
    std::pair<int, int> coordinates;
    int detectionRadius;
public:
    /**
     * @brief Конструктор класса Fighter.
     * @param _model Модель истребителя.
     * @param _maxHP Максимальное количество здоровья.
     * @param _speed Скорость истребителя.
     * @param _maxNumEquipment Максимальное количество вооружения.
     * @param _equipment Вектор указателей на вооружение.
     * @param _coordinates Координаты истребителя.
     * @param _detectionRadius Радиус обнаружения истребителя.
     */
    Fighter(std::string _model, int _HP, int _maxHP, int _speed,
            int _maxNumEquipment, const std::pair<int, int> &_coordinates,
            int _detectionRadius)
            : model(std::move(_model)), HP(_HP), maxHP(_maxHP), speed(_speed),
              maxNumEquipment(_maxNumEquipment), coordinates(_coordinates),
              detectionRadius(_detectionRadius) {};

    /**
     * @brief Возвращает модель истребителя.
     * @return Модель истребителя.
     */
    [[nodiscard]] std::string getModel() const { return model; };

    /**
     * @brief Устанавливает модель истребителя.
     * @param value Новая модель истребителя.
     */
    void setModel(std::string value) { model = value; };

    /**
     * @brief Возвращает текущее количество здоровья.
     * @return Текущее количество здоровья.
     */
    [[nodiscard]] int getHP() const { return HP; };

    /**
     * @brief Устанавливает количество здоровья.
     * @param value Новое количество здоровья.
     */
    void setHP(int value) { HP = value; };

    /**
     * @brief Возвращает максимальное количество здоровья.
     * @return Максимальное количество здоровья.
     */
    [[nodiscard]] int getMaxHP() const { return maxHP; };

    /**
     * @brief Устанавливает максимальное количество здоровья.
     * @param value Новое максимальное количество здоровья.
     */
    void setMaxSurvivability(int value) { maxHP = value; };

    /**
     * @brief Возвращает скорость истребителя.
     * @return Скорость истребителя.
     */
    [[nodiscard]] int getSpeed() const { return speed; };

    /**
     * @brief Устанавливает скорость истребителя.
     * @param value Новая скорость истребителя.
     */
    void setSpeed(int value) { speed = value; };

    /**
     * @brief Возвращает максимальное количество вооружения.
     * @return Максимальное количество вооружения.
     */
    [[nodiscard]] int getMaxNumEquipment() const { return maxNumEquipment; };

    /**
     * @brief Устанавливает максимальное количество вооружения.
     * @param value Новое максимальное количество вооружения.
     */
    void setMaxNumEquipment(int value) { maxNumEquipment = value; };

    /**
     * @brief Возвращает вектор указателей на вооружение.
     * @return Вектор указателей на вооружение.
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Weapon>> &getEquipment() const { return equipment; }

    /**
     * @brief Устанавливает новый вектор указателей на вооружение.
     * @param newEquipment Новый вектор указателей на вооружение.
     */
    void setEquipment(const std::vector<std::shared_ptr<Weapon>> &_equipment) { equipment = _equipment; }

    /**
     * @brief Возвращает координаты истребителя.
     * @return Координаты истребителя.
     */
    [[nodiscard]] std::pair<int, int> getCoordinates() const { return coordinates; };

    /**
     * @brief Устанавливает новые координаты истребителя.
     * @param value Новые координаты истребителя.
     */
    void setCoordinates(std::pair<int, int> value) { coordinates = value; };

    /**
     * @brief Устанавливает радиус обнаружения истребителя.
     * @param value Новый радиус обнаружения истребителя.
     */
    void setDetectionRadius(int value) { detectionRadius = value; };

    /**
     * @brief Виртуальная функция для получения урона от снаряда.
     * @param prg Снаряд, который наносит урон.
     */
    virtual void getDamage(Projectile prg);

    /**
     * @brief Виртуальная функция для получения радиуса атаки истребителя.
     * @return Радиус атаки истребителя.
     */
    virtual int getAttackRadius();

    /**
     * @brief Виртуальная функция для получения радиуса обнаружения истребителя.
     * @return Радиус обнаружения истребителя.
     */
    virtual int getDetectionRadius();

    /**
     * @brief Виртуальная функция для попытки атаки другого истребителя.
     * @param target Цель атаки (другой истребитель).
     * @param weapon Вооружение для атаки.
     * @return true, если есть попадание, false в противном случае.
     */
    virtual bool attemptAttack(std::shared_ptr<Fighter> target, std::shared_ptr<Weapon> weapon);

    /**
     * @brief Функция для получения оружия с максимальным уроном.
     * @return Оружие с максимальным уроном.
     */
    std::shared_ptr<Weapon> getMostPowerfulWeapon() const;

    /**
     * @brief Функция которая определяет жив ли самолет.
     * @return если жив - true, false - если умер.
     */
    const bool isDead() {
        if (HP <= 0) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief Виртуальный деструктор по умолчанию.
     */
    virtual ~Fighter() = default;
};

#endif //_FIGHTER_H
