#include "testdatabase.h"
#include "../OOP2Lab/databasemanager.h"
#include <QFile>
#include <QDir>
#include <QSqlQuery>

void TestDatabase::initTestCase() {
    m_testDbPath = QDir::currentPath() + "/pure_test_db.sqlite";
}

void TestDatabase::cleanupTestCase() {
    DatabaseManager::instance().close();
    QFile::remove(m_testDbPath);
}

void TestDatabase::testSingletonInstance() {
    DatabaseManager& instance1 = DatabaseManager::instance();
    DatabaseManager& instance2 = DatabaseManager::instance();

    QCOMPARE(&instance1, &instance2);
}

void TestDatabase::testInitializationAndTablesCreation() {
    DatabaseManager& db = DatabaseManager::instance();

    bool ok = db.init(m_testDbPath);
    QVERIFY(ok);
    QVERIFY(QFile::exists(m_testDbPath));

    QSqlQuery checkQuery;
    checkQuery.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='links'");

    QVERIFY(checkQuery.next());
    QCOMPARE(checkQuery.value(0).toString(), QString("links"));
}
