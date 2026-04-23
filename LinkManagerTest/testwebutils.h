#ifndef TESTWEBUTILS_H
#define TESTWEBUTILS_H

#include <QObject>
#include <QtTest>

class TestWebUtils : public QObject {
    Q_OBJECT

private slots:
    void testFetchTitleSuccess();
    void testFetchTitleInvalidUrl();
};

#endif // TESTWEBUTILS_H
