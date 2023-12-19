#ifndef LAB3_TABLE_H
#define LAB3_TABLE_H

#include <iostream>
#include <list>

/**
 * @brief Шаблонный класс Table для хранения данных истребителей.
 * @tparam T Тип данных, представляющих истребителя.
 */
template<typename T>
class Table {
private:
    std::list<std::pair<std::unique_ptr<T>, std::string>> data;

public:
    /**
     * @brief Добавляет элемент в таблицу.
     * @param item Указатель на элемент, который добавляется в таблицу.
     * @param callSign Позывной элемента.
     */
    void addItem(std::unique_ptr<T> item, const std::string &callSign) {
        data.emplace_back(std::move(item), callSign);
    }

    /**
     * @brief Удаляет элемент из таблицы по его позывному.
     * @param callSign Позывной элемента, который нужно удалить.
     */
    void removeItem(const std::string &callSign) {
        data.remove_if([callSign](const auto &item) {
            return item.second == callSign;
        });
    }

    /**
     * @brief Получает "описатель звена" по его позывному.
     * @param callSign Позывной элемента, который нужно получить.
     * @return Указатель на "описатель звена" или nullptr, если элемент не найден.
     */
    std::unique_ptr<T> getEchelonByCallSign(const std::string &callSign) {
        auto it = std::find_if(data.begin(), data.end(), [callSign](const auto &item) {
            return item.second == callSign;
        });
        if (it != data.end()) {
            return std::move(it->first);
        }
        return nullptr;
    }

    /**
     * @brief Получает количество элементов в таблице.
     * @return Количество элементов в таблице.
     */
    [[nodiscard]] int getCount() const {
        return data.size();
    }

    /**
     * @brief Класс-итератор для перебора элементов таблицы.
     */
    class Iterator {
    private:
        typename std::list<std::pair<std::unique_ptr<T>, std::string>>::iterator current;
    public:
        /**
         * @brief Конструктор итератора.
         * @param iter Итератор, передаваемый из внешнего контекста.
         */
        Iterator(typename std::list<std::pair<std::unique_ptr<T>, std::string>>::iterator iter)
                : current(iter) {}

        /**
         * @brief Перемещает итератор к следующему элементу.
         * @return Ссылка на сам итератор после перемещения.
         */
        Iterator &operator++() {
            ++current;
            return *this;
        }

        /**
         * @brief Проверяет, не достиг ли итератор конца коллекции.
         * @param other Другой итератор для сравнения.
         * @return true, если итераторы не равны; false в противном случае.
         */
        bool operator!=(const Iterator &other) const {
            return current != other.current;
        }

        /**
         * @brief Возвращает ссылку на текущий элемент коллекции.
         * @return Ссылка на текущий элемент коллекции.
         */
        std::pair<std::unique_ptr<T>, std::string> &operator*() {
            return *current;
        }
    };

    /**
     * @brief Возвращает итератор, указывающий на начало коллекции.
     * @return Итератор, указывающий на начало коллекции.
     */
    Iterator begin() {
        return Iterator(data.begin());
    }

    /**
     * @brief Возвращает итератор, указывающий за конец коллекции.
     * @return Итератор, указывающий за конец коллекции.
     */
    Iterator end() {
        return Iterator(data.end());
    }
};

#endif //LAB3_TABLE_H
