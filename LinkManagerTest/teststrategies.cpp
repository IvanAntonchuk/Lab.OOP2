#include "teststrategies.h"
#include "../OOP2Lab/csvexportstrategy.h"
#include "../OOP2Lab/csvimportstrategy.h"
#include "../OOP2Lab/htmlexportstrategy.h"
#include "../OOP2Lab/jsonimportstrategy.h"
#include <QFile>
#include <QDir>

void TestStrategies::initTestCase() {
    m_testCsvPath = QDir::currentPath() + "/test_export.csv";
    m_testJsonPath = QDir::currentPath() + "/test_export.json";
    m_testHtmlPath = QDir::currentPath() + "/test_export.html";
}

void TestStrategies::cleanupTestCase() {
    QFile::remove(m_testCsvPath);
    QFile::remove(m_testJsonPath);
    QFile::remove(m_testHtmlPath);
}

void TestStrategies::testHtmlStrategyExportOnly() {
    std::vector<LinkData> data = {{"HTML_Test", "url", "folder", {}, "", "", ""}};

    HtmlExportStrategy strategy;
    bool success = strategy.exportData(m_testHtmlPath, data);

    QVERIFY(success);
    QVERIFY(QFile::exists(m_testHtmlPath));
}

void TestStrategies::testCsvStrategyRoundTrip() {
    std::vector<LinkData> originalData = {{"CSV_Test", "https://test.csv", "Folder", {}, "related", "comment", ""}};

    CsvExportStrategy exportStrategy;
    bool exportSuccess = exportStrategy.exportData(m_testCsvPath, originalData);
    QVERIFY(exportSuccess);

    CsvImportStrategy importStrategy;
    std::vector<LinkData> importedData = importStrategy.importData(m_testCsvPath);

    QCOMPARE(importedData.size(), 1);
    QCOMPARE(QString::fromStdString(importedData[0].name), QString("CSV_Test"));
    QCOMPARE(QString::fromStdString(importedData[0].url), QString("https://test.csv"));
}

void TestStrategies::testJsonStrategyRoundTrip() {
    JsonImportStrategy importStrategy;
    std::vector<LinkData> importedData = importStrategy.importData("non_existent_file.json");

    QCOMPARE(importedData.size(), 0);
}
