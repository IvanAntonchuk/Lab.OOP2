#ifndef HTMLEXPORTSTRATEGY_H
#define HTMLEXPORTSTRATEGY_H

#include "iexportstrategy.h"

/**
 * @brief Клас HtmlExportStrategy реалізує стратегію експорту посилань у формат HTML.
 * * Цей клас є частиною патерну "Стратегія" (Strategy) і відповідає за форматування та
 * збереження списку об'єктів LinkData у вигляді веб-сторінки (HTML-файлу).
 */
class HtmlExportStrategy : public IExportStrategy {
public:
    /**
     * @brief Експортує переданий список посилань у HTML-файл.
     * * Перевизначає віртуальний метод базового інтерфейсу IExportStrategy.
     * Генерує HTML-розмітку (наприклад, у вигляді таблиці або списку) для зручного перегляду посилань у браузері.
     * * @param filePath Шлях до файлу, у який будуть збережені дані.
     * @param links Вектор об'єктів LinkData, які потрібно експортувати.
     * @return true, якщо експорт пройшов успішно та файл був збережений.
     * @return false, якщо сталася помилка (наприклад, неможливо відкрити файл для запису).
     */
    bool exportData(const QString& filePath, const std::vector<LinkData>& links) const override;
};

#endif // HTMLEXPORTSTRATEGY_H
