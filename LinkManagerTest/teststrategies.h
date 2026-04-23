#ifndef TESTSTRATEGIES_H
#define TESTSTRATEGIES_H

#include <QObject>
#include <QtTest>

class TestStrategies : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testHtmlStrategyExportOnly();
    void testCsvStrategyRoundTrip();
    void testJsonStrategyRoundTrip();

private:
    QString m_testCsvPath;
    QString m_testJsonPath;
    QString m_testHtmlPath;
};

#endif // TESTSTRATEGIES_H
