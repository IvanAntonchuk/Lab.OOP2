#ifndef TESTDATABASE_H
#define TESTDATABASE_H

#include <QObject>
#include <QtTest>

class TestDatabase : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testSingletonInstance();
    void testInitializationAndTablesCreation();

private:
    QString m_testDbPath;
};

#endif // TESTDATABASE_H
