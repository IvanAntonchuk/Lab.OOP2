#include "testwebutils.h"
#include "../OOP2Lab/webutils.h"
#include <QSignalSpy>

void TestWebUtils::testFetchTitleSuccess() {
    WebUtils webUtils;

    QSignalSpy spy(&webUtils, &WebUtils::titleReady);

    webUtils.fetchTitleAsync("http://example.com");

    QVERIFY(spy.wait(5000));

    QCOMPARE(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).toString(), QString("http://example.com"));
    QCOMPARE(arguments.at(1).toString(), QString("Example Domain"));
}

void TestWebUtils::testFetchTitleInvalidUrl() {
    WebUtils webUtils;
    QSignalSpy spy(&webUtils, &WebUtils::titleReady);

    QString badUrl = "http://this-is-a-completely-invalid-url-12345.com";
    webUtils.fetchTitleAsync(badUrl);

    QVERIFY(spy.wait(5000));

    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).toString(), badUrl);

    QCOMPARE(arguments.at(1).toString(), badUrl);
}
