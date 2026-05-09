#ifndef JSONIMPORTSTRATEGY_H
#define JSONIMPORTSTRATEGY_H

#include "iimportstrategy.h"

/**
 * @brief Клас JsonImportStrategy реалізує стратегію імпорту посилань із формату JSON.
 * * Цей клас є частиною патерну "Стратегія" (Strategy) і відповідає за зчитування даних із
 * файлу у форматі JSON (JavaScript Object Notation) та їх перетворення у список об'єктів LinkData.
 */
class JsonImportStrategy : public IImportStrategy {
public:
    /**
     * @brief Імпортує список посилань із вказаного JSON-файлу.
     * * Перевизначає віртуальний метод базового інтерфейсу IImportStrategy.
     * Здійснює парсинг JSON-структури та витягує необхідні дані для формування об'єктів посилань.
     * * @param filePath Шлях до JSON-файлу, з якого будуть зчитані дані.
     * @return Вектор об'єктів LinkData, успішно імпортованих із файлу. Якщо файл некоректний,
     * не знайдений або порожній, повернеться порожній вектор.
     */
    std::vector<LinkData> importData(const QString& filePath) const override;
};

#endif // JSONIMPORTSTRATEGY_H
