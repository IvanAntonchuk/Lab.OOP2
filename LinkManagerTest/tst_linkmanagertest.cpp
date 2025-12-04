#include <QtTest>
#include <QFile>
#include "linkmanager.h"
#include "linkserializer.h"

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
    void testPersistence();
    void testLinkSerializer();
    void testEdgeCases();
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

void LinkManagerTest::testPersistence()
{
    QString tempFileName = "test_data.json";

    if (QFile::exists(tempFileName)) {
        QFile::remove(tempFileName);
    }

    LinkManager managerToSave;

    managerToSave.addFolder("Work");
    managerToSave.addContext("Important");

    LinkData link;
    link.name = "Test Save";
    link.url = "https://example.com";
    link.folder = "Work";
    link.contexts = {"Important"};
    link.comment = "Persisted comment";

    managerToSave.addLink(link);

    bool saved = managerToSave.saveToFile(tempFileName.toStdString());
    QVERIFY2(saved, "Failed to save file to disk");

    LinkManager managerToLoad;
    bool loaded = managerToLoad.loadFromFile(tempFileName.toStdString());
    QVERIFY2(loaded, "Failed to load file from disk");

    const std::vector<LinkData>& links = managerToLoad.getLinks();
    QCOMPARE(links.size(), 1);

    const LinkData& loadedLink = links[0];
    QCOMPARE(QString::fromStdString(loadedLink.name), "Test Save");
    QCOMPARE(QString::fromStdString(loadedLink.url), "https://example.com");
    QCOMPARE(QString::fromStdString(loadedLink.folder), "Work");
    QCOMPARE(QString::fromStdString(loadedLink.comment), "Persisted comment");

    QVERIFY(!loadedLink.contexts.empty());
    QCOMPARE(QString::fromStdString(loadedLink.contexts[0]), "Important");

    QVERIFY(managerToLoad.hasFolder("Work"));
    QVERIFY(managerToLoad.hasContext("Important"));

    QFile::remove(tempFileName);
}

void LinkManagerTest::testLinkSerializer()
{
    std::vector<LinkData> originalLinks;
    LinkData l1;
    l1.name = "Google";
    l1.url = "https://google.com";
    l1.folder = "Search";
    l1.contexts = {"Web", "Tool"};
    l1.comment = "Main search engine";
    originalLinks.push_back(l1);

    QString csvData = "Google;https://google.com;Search;Web;Main search engine\n";

    std::vector<LinkData> importedLinks = LinkSerializer::importFromCSV(csvData);

    QCOMPARE(importedLinks.size(), 1);
    QCOMPARE(QString::fromStdString(importedLinks[0].name), "Google");
    QCOMPARE(QString::fromStdString(importedLinks[0].url), "https://google.com");
    QCOMPARE(QString::fromStdString(importedLinks[0].folder), "Search");
    QCOMPARE(QString::fromStdString(importedLinks[0].comment), "Main search engine");

    QVERIFY(!importedLinks[0].contexts.empty());
    QCOMPARE(QString::fromStdString(importedLinks[0].contexts[0]), "Web");

    QString harvardStr = LinkSerializer::exportLinks(originalLinks, LinkSerializer::Harvard);
    QString expectedHarvard = "Google. Available at: https://google.com. (Notes: Main search engine).\n";
    QCOMPARE(harvardStr, expectedHarvard);
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

QTEST_APPLESS_MAIN(LinkManagerTest)

#include "tst_linkmanagertest.moc"
