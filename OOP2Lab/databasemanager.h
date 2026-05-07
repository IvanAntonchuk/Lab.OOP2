#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

/**
 * @brief Клас DatabaseManager відповідає за управління з'єднанням з базою даних SQLite.
 * * Цей клас реалізує патерн "Одинак" (Singleton), гарантуючи, що в програмі
 * існує лише одне підключення до бази даних у будь-який момент часу.
 */
class DatabaseManager
{
public:
    /**
     * @brief Отримує єдиний екземпляр класу DatabaseManager.
     * @return Посилання на статичний об'єкт DatabaseManager.
     */
    static DatabaseManager& instance();

    /**
     * @brief Ініціалізує з'єднання з базою даних.
     * Відкриває базу даних за вказаним шляхом та автоматично створює необхідні таблиці,
     * якщо вони ще не існують.
     * @param path Шлях до файлу бази даних SQLite.
     * @return true, якщо ініціалізація та відкриття бази пройшли успішно, інакше false.
     */
    bool init(const QString& path);

    /**
     * @brief Закриває з'єднання з базою даних.
     * Викликається для безпечного завершення роботи з базою.
     */
    void close();

private:
    /**
     * @brief Приватний конструктор (частина патерну Singleton).
     */
    DatabaseManager() = default;

    /**
     * @brief Приватний деструктор.
     */
    ~DatabaseManager();

    /**
     * @brief Видалений конструктор копіювання для запобігання створенню копій (Singleton).
     */
    DatabaseManager(const DatabaseManager&) = delete;

    /**
     * @brief Видалений оператор присвоювання для запобігання копіюванню (Singleton).
     */
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    /**
     * @brief Об'єкт бази даних Qt.
     */
    QSqlDatabase db;

    /**
     * @brief Створює необхідні таблиці в базі даних, якщо вони відсутні.
     * @return true, якщо таблиці успішно створено або вони вже існують, інакше false.
     */
    bool createTables();
};

#endif // DATABASEMANAGER_H
