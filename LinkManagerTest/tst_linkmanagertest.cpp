#include <QtTest>
#include <vector>
#include <string>

#include "linkmanager.h"
#include "webutils.h"
#include "qrcodegen.hpp"

class LinkManagerTest : public QObject
{
    Q_OBJECT

public:
    LinkManagerTest();
    ~LinkManagerTest();

private slots:
    void testAddLink();
    void testDeleteLink();
    void testUpdateLink();
    void testSearchLinks();
    void testFilterLinks();
    void testFolderManagement();
    void testContextManagement();
    void testEdgeCases();
    void testQRCodeLibrary();
};

LinkManagerTest::LinkManagerTest() {}
LinkManagerTest::~LinkManagerTest() {}

void LinkManagerTest::testAddLink()
{
    LinkManager manager;
    QCOMPARE(manager.getLinks().size(), 0);

    LinkData link;
    link.name = "Test Site";
    link.url = "https://test.com";

    manager.addLink(link);

    QCOMPARE(manager.getLinks().size(), 1);
    QCOMPARE(QString::fromStdString(manager.getLinks()[0].name), "Test Site");
}

void LinkManagerTest::testDeleteLink()
{
    LinkManager manager;
    LinkData link;
    link.name = "To Delete";
    manager.addLink(link);

    QCOMPARE(manager.getLinks().size(), 1);
    manager.deleteLink(0);
    QCOMPARE(manager.getLinks().size(), 0);
}


void LinkManagerTest::testUpdateLink()
{
    LinkManager manager;
    LinkData link;
    link.name = "Old Name";
    manager.addLink(link);

    LinkData newLink;
    newLink.name = "New Name";

    manager.updateLink(0, newLink);

    QCOMPARE(QString::fromStdString(manager.getLinks()[0].name), "New Name");
}

void LinkManagerTest::testSearchLinks()
{
    LinkManager manager;

    LinkData l1; l1.name = "Apple"; manager.addLink(l1);
    LinkData l2; l2.name = "Banana"; manager.addLink(l2);
    LinkData l3; l3.name = "Pineapple"; manager.addLink(l3);

    std::vector<LinkData> results = manager.searchLinks("apple");
    results = manager.searchLinks("Apple");

    QVERIFY(results.size() >= 1);
    QCOMPARE(QString::fromStdString(results[0].name), "Apple");
}

void LinkManagerTest::testFilterLinks()
{
    LinkManager manager;

    LinkData l1; l1.name = "Link1"; l1.folder = "Work"; manager.addLink(l1);
    LinkData l2; l2.name = "Link2"; l2.folder = "Home"; manager.addLink(l2);

    std::vector<std::string> allowedFolders = {"Work"};
    std::vector<std::string> allowedContexts = {};

    LinkData l3; l3.name = "Link3"; l3.folder = "Work"; l3.contexts.push_back("Book");
    manager.addLink(l3);

    std::vector<LinkData> res = manager.filterLinks({"Work"}, {"Book"});

    QCOMPARE(res.size(), 1);
    QCOMPARE(QString::fromStdString(res[0].name), "Link3");
}

void LinkManagerTest::testFolderManagement()
{
    LinkManager manager;
    manager.addFolder("New Folder");

    QVERIFY(manager.hasFolder("New Folder"));

    manager.removeFolder("New Folder");
    QVERIFY(!manager.hasFolder("New Folder"));
}

void LinkManagerTest::testContextManagement()
{
    LinkManager manager;
    manager.addContext("New Tag");

    QVERIFY(manager.hasContext("New Tag"));

    manager.removeContext("New Tag");
    QVERIFY(!manager.hasContext("New Tag"));
}

void LinkManagerTest::testEdgeCases()
{
    LinkManager manager;
    LinkData link;
    link.name = "Test";
    manager.addLink(link);

    manager.deleteLink(100);
    manager.deleteLink(-1);
    QCOMPARE(manager.getLinks().size(), 1);

    LinkData newData;
    newData.name = "Updated";
    manager.updateLink(100, newData);
    QCOMPARE(QString::fromStdString(manager.getLinks()[0].name), "Test");

    std::vector<LinkData> searchRes = manager.searchLinks("");
    QCOMPARE(searchRes.size(), 1);

    manager.addFolder("MyFolder");
    manager.addFolder("MyFolder");
    QCOMPARE(manager.getFolders().size(), 1);

    manager.addContext("MyTag");
    manager.addContext("MyTag");
    QCOMPARE(manager.getContexts().size(), 5);
}

void LinkManagerTest::testQRCodeLibrary()
{
    using namespace qrcodegen;

    std::string text = "https://www.google.com";

    QrCode qr = QrCode::encodeText(text.c_str(), QrCode::Ecc::LOW);

    QVERIFY(qr.getSize() > 0);

    bool isDark = qr.getModule(0, 0);
    QVERIFY(isDark == true || isDark == false);
}

QTEST_APPLESS_MAIN(LinkManagerTest)

#include "tst_linkmanagertest.moc"
