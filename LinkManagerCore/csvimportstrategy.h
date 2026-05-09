#ifndef CSVIMPORTSTRATEGY_H
#define CSVIMPORTSTRATEGY_H

#include "iimportstrategy.h"

/**
 * @brief Клас CsvImportStrategy реалізує стратегію імпорту посилань із формату CSV.
 * * Цей клас є частиною патерну "Стратегія" (Strategy) і відповідає за зчитування даних із
 * текстового файлу з роздільниками (Comma-Separated Values) та їх перетворення у
 * список об'єктів LinkData.
 */
class CsvImportStrategy : public IImportStrategy {
public:
    /**
     * @brief Імпортує список посилань із вказаного CSV-файлу.
     * * Перевизначає віртуальний метод базового інтерфейсу IImportStrategy.
     * * @param filePath Шлях до CSV-файлу, з якого будуть зчитані дані.
     * @return Вектор об'єктів LinkData, успішно імпортованих із файлу. Якщо файл не
     * знайдено, його неможливо прочитати або він порожній, повернеться порожній вектор.
     */
    std::vector<LinkData> importData(const QString& filePath) const override;
};

#endif // CSVIMPORTSTRATEGY_H
