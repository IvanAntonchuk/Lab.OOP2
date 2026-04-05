/**
 * @file linkserializer.h
 * @brief Клас для серіалізації та десеріалізації даних посилань.
 *
 * Забезпечує експорт посилань у різні формати (BibTeX, ДСТУ, Harvard)
 * та імпорт з CSV/JSON.
 */

#ifndef LINKSERIALIZER_H
#define LINKSERIALIZER_H

#include <QString>
#include <vector>
#include "linkmanager.h"

/**
 * @class LinkSerializer
 * @brief Статичний клас-помічник для конвертації даних.
 */
class LinkSerializer
{
public:
    /**
     * @enum ExportFormat
     * @brief Доступні формати для експорту списку посилань.
     */
    enum ExportFormat {
        SimpleList, ///< Простий текстовий список.
        BibTeX,     ///< Формат BibTeX для використання в LaTeX.
        DSTU8302,   ///< Оформлення згідно ДСТУ 8302:2015 (Україна).
        Harvard     ///< Гарвардський стиль цитування.
    };

    /**
     * @brief Генерує текстовий звіт з посилань у вказаному форматі.
     * @param links Вектор посилань для експорту.
     * @param format Обраний формат експорту (з переліку ExportFormat).
     * @return Рядок (QString) з відформатованим текстом.
     */
    static QString exportLinks(const std::vector<LinkData>& links, ExportFormat format);

    /**
     * @brief Імпортує посилання з тексту у форматі CSV.
     * Очікуваний формат: Назва;URL;Папка;Контекст;Коментар
     * @param csvContent Вміст CSV файлу.
     * @return Вектор розпізнаних об'єктів LinkData.
     */
    static std::vector<LinkData> importFromCSV(const QString& csvContent);

    /**
     * @brief Імпортує посилання з даних у форматі JSON.
     * @param jsonData Байтовий масив з JSON даними.
     * @return Вектор розпізнаних об'єктів LinkData.
     */
    static std::vector<LinkData> importFromJSON(const QByteArray& jsonData);
};

#endif // LINKSERIALIZER_H
