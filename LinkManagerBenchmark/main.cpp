#include <QtTest>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>

#include "linkmanager.h"
#include "databasemanager.h"
#include "csvexportstrategy.h"

class BenchmarkTest : public QObject {
    Q_OBJECT

private slots:
    void initTestCase() {
        QString dbPath = QDir::currentPath() + "/benchmark_db.sqlite";
        DatabaseManager::instance().init(dbPath);
        qDebug() << "Benchmark DB initialized.";
    }

    void cleanupTestCase() {
        DatabaseManager::instance().close();
        QFile::remove(QDir::currentPath() + "/benchmark_db.sqlite");
        QFile::remove("benchmark_export.csv");
        qDebug() << "Benchmark DB cleaned up.";
    }

    void benchmarkMassInsert() {
        LinkManager manager;
        static int iterationOffset = 0;

        QBENCHMARK {
            for (int i = 0; i < 100; ++i) {
                QString url = "https://bench_" + QString::number(iterationOffset) + "_" + QString::number(i) + ".com";

                LinkData data;
                data.url = url.toStdString();
                data.name = "Test Title";
                data.folder = "Benchmarks";
                data.comment = "Mass insert test";

                manager.addLink(data);
            }
            iterationOffset++;
        }
    }

    void benchmarkColdStartLoad() {
        LinkManager manager;
        QBENCHMARK {
            manager.loadFromFile("");
        }
    }

    void benchmarkSearch() {
        LinkManager manager;
        manager.loadFromFile("");

        QBENCHMARK {
            manager.searchLinks("Test Title");
        }
    }

    void benchmarkCsvExport() {
        LinkManager manager;
        manager.loadFromFile("");
        auto links = manager.getLinks();

        CsvExportStrategy csvExport;
        QBENCHMARK {
            csvExport.exportData("benchmark_export.csv", links);
        }
    }
};

QTEST_MAIN(BenchmarkTest)
#include "main.moc"
