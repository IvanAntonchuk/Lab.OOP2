#include "databasemanager.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager _instance;
    return _instance;
}

DatabaseManager::~DatabaseManager()
{
    close();
}

bool DatabaseManager::init(const QString& path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open()) {
        qDebug() << "Помилка: Не вдалося відкрити базу даних." << db.lastError().text();
        return false;
    }

    return createTables();
}

void DatabaseManager::close()
{
    if (db.isOpen()) {
        db.close();
    }
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;
    bool success = true;

    QString createLinksTable = R"(
        CREATE TABLE IF NOT EXISTS links (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            url TEXT NOT NULL,
            folder TEXT,
            related_url TEXT,
            comment TEXT,
            icon_data TEXT
        )
    )";

    if (!query.exec(createLinksTable)) {
        qDebug() << "Помилка створення таблиці links:" << query.lastError().text();
        success = false;
    }

    QString createContextsTable = R"(
        CREATE TABLE IF NOT EXISTS link_contexts (
            link_id INTEGER,
            context_name TEXT,
            FOREIGN KEY(link_id) REFERENCES links(id) ON DELETE CASCADE
        )
    )";

    if (!query.exec(createContextsTable)) {
        qDebug() << "Помилка створення таблиці link_contexts:" << query.lastError().text();
        success = false;
    }

    query.exec("CREATE TABLE IF NOT EXISTS folders (name TEXT PRIMARY KEY)");
    query.exec("CREATE TABLE IF NOT EXISTS contexts (name TEXT PRIMARY KEY)");

    return success;
}
