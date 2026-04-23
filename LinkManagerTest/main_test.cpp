#include <QCoreApplication>
#include <QTest>
#include <iostream>

#include "testlinkmanager.h"
#include "teststrategies.h"
#include "testdatabase.h"
#include "testwebutils.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    int status = 0;

    auto runTest = [&](QObject* testObject) {
        status |= QTest::qExec(testObject, argc, argv);
    };

    std::cout << "STARTING COMPREHENSIVE TEST SUITE" << std::endl;

    runTest(new TestDatabase());
    runTest(new TestLinkManager());
    runTest(new TestStrategies());
    runTest(new TestWebUtils());

    std::cout << "ALL TESTS FINISHED" << std::endl;
    return status;
}
