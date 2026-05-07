#ifndef CSVEXPORTSTRATEGY_H
#define CSVEXPORTSTRATEGY_H

#include "iexportstrategy.h"

/**
 * @brief Клас CsvExportStrategy реалізує стратегію експорту посилань у формат CSV.
 * * Цей клас є частиною патерну "Стратегія" (Strategy) і відповідає за збереження списку
 * об'єктів LinkData у текстовий файл із роздільниками (Comma-Separated Values).
 */
class CsvExportStrategy : public IExportStrategy {
public:
    /**
     * @brief Експортує переданий список посилань у CSV-файл.
     * * Перевизначає віртуальний метод базового інтерфейсу IExportStrategy.
     * * @param filePath Шлях до файлу, у який будуть збережені дані.
     * @param links Вектор об'єктів LinkData, які потрібно експортувати.
     * @return true, якщо експорт пройшов успішно та файл був збережений.
     * @return false, якщо сталася помилка (наприклад, неможливо відкрити файл для запису).
     */
    bool exportData(const QString& filePath, const std::vector<LinkData>& links) const override;
};

#endif // CSVEXPORTSTRATEGY_H
