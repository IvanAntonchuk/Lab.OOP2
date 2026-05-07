/**
 * @file teststrategies.h
 * @brief Заголовочний файл для тестування стратегій експорту та імпорту даних.
 */

#ifndef TESTSTRATEGIES_H
#define TESTSTRATEGIES_H

#include <QObject>
#include <QtTest>

/**
 * @class TestStrategies
 * @brief Клас модульних тестів для перевірки реалізацій патерну "Стратегія".
 *
 * Цей клас перевіряє коректність роботи всіх стратегій експорту (CSV, HTML)
 * та імпорту (CSV, JSON). Основна увага приділяється цілісності даних при
 * циклічному перетворенні (експорт -> імпорт).
 */
class TestStrategies : public QObject {
    Q_OBJECT

private slots:
    /**
     * @brief Глобальна ініціалізація тестового набору.
     * Готує шляхи до тимчасових файлів, які будуть використовуватися для запису
     * та зчитування даних під час тестів.
     */
    void initTestCase();

    /**
     * @brief Глобальне очищення після завершення тестів.
     * Видаляє всі тимчасові файли (CSV, JSON, HTML), створені під час тестування стратегій.
     */
    void cleanupTestCase();

    /**
     * @brief Тестує стратегію експорту в HTML.
     * Оскільки HTML є форматом тільки для читання (візуалізації), перевіряється
     * лише успішність створення файлу та коректність його формування.
     */
    void testHtmlStrategyExportOnly();

    /**
     * @brief Тестує повний цикл роботи з CSV (RoundTrip).
     * Перевіряє, чи дані, експортовані у CSV, ідентичні тим, що будуть
     * отримані після зворотного імпорту з цього ж файлу.
     */
    void testCsvStrategyRoundTrip();

    /**
     * @brief Тестує повний цикл роботи з JSON (RoundTrip).
     * Перевіряє коректність серіалізації та десеріалізації об'єктів LinkData
     * за допомогою формату JSON.
     */
    void testJsonStrategyRoundTrip();

private:
    /** @brief Шлях до тимчасового файлу для тестів CSV. */
    QString m_testCsvPath;
    /** @brief Шлях до тимчасового файлу для тестів JSON. */
    QString m_testJsonPath;
    /** @brief Шлях до тимчасового файлу для тестів HTML. */
    QString m_testHtmlPath;
};

#endif // TESTSTRATEGIES_H
