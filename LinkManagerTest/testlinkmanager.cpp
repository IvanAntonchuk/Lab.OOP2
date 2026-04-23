#include "testlinkmanager.h"
#include "../OOP2Lab/linkmanager.h"
#include "../OOP2Lab/databasemanager.h"
#include <QSqlQuery>
#include <QDir>

void TestLinkManager::initTestCase() {
    if (!QSqlDatabase::database().isOpen()) {
        DatabaseManager::instance().init(QDir::currentPath() + "/test_links.db");
    }
}

void TestLinkManager::cleanupTestCase() {
    QFile::remove(QDir::currentPath() + "/test_links.db");
}

void TestLinkManager::init() {
    QSqlQuery().exec("DELETE FROM link_contexts");
    QSqlQuery().exec("DELETE FROM links");
    QSqlQuery().exec("DELETE FROM folders");
    QSqlQuery().exec("DELETE FROM contexts");
}

void TestLinkManager::testAddLinkBasic() {
    LinkManager manager;
    manager.addLink({"Basic", "url", "Folder", {}, "", "", ""});
    QCOMPARE(manager.getLinks().size(), 1);
    QCOMPARE(QString::fromStdString(manager.getLinks()[0].name), QString("Basic"));
    QVERIFY(manager.hasFolder("Folder"));
}

void TestLinkManager::testAddLinkEmptyData() {
    LinkManager manager;
    manager.addLink(LinkData());
    QCOMPARE(manager.getLinks().size(), 1);
}

void TestLinkManager::testAddLinkDuplicateContexts() {
    LinkManager manager;
    manager.addLink({"DupCtx", "url", "F", {"Dup", "Dup"}, "", "", ""});
    manager.addContext("Dup");
    int dupCount = 0;
    for(const auto& c : manager.getContexts()) {
        if (c == "Dup") dupCount++;
    }
    QCOMPARE(dupCount, 1);
}

void TestLinkManager::testDeleteLinkValidIndex() {
    LinkManager manager;
    manager.addLink({"L1", "", "", {}, "", "", ""});
    manager.addLink({"L2", "", "", {}, "", "", ""});
    manager.deleteLink(0);
    QCOMPARE(manager.getLinks().size(), 1);
    QCOMPARE(QString::fromStdString(manager.getLinks()[0].name), QString("L2"));
}

void TestLinkManager::testDeleteLinkInvalidIndexBounds() {
    LinkManager manager;
    manager.addLink({"L1", "", "", {}, "", "", ""});
    manager.deleteLink(-1);
    manager.deleteLink(5);
    QCOMPARE(manager.getLinks().size(), 1);
}

void TestLinkManager::testDeleteLinkEmptyManager() {
    LinkManager manager;
    manager.deleteLink(0);
    QCOMPARE(manager.getLinks().size(), 0);
}

void TestLinkManager::testUpdateLinkValid() {
    LinkManager manager;
    manager.addLink({"Old", "u", "f", {}, "", "", ""});
    manager.updateLink(0, {"New", "u2", "f2", {}, "", "", ""});
    QCOMPARE(QString::fromStdString(manager.getLinks()[0].name), QString("New"));
}

void TestLinkManager::testUpdateLinkCreatesNewFolders() {
    LinkManager manager;
    manager.addLink({"L1", "u", "OldFolder", {}, "", "", ""});
    manager.updateLink(0, {"L1", "u", "NewFolder", {}, "", "", ""});
    QVERIFY(manager.hasFolder("NewFolder"));
}

void TestLinkManager::testSearchMatchName() {
    LinkManager manager;
    manager.addLink({"FindMe", "", "", {}, "", "", ""});
    QCOMPARE(manager.searchLinks("Find").size(), 1);
}

void TestLinkManager::testSearchMatchUrl() {
    LinkManager manager;
    manager.addLink({"Name", "https://github.com", "", {}, "", "", ""});
    QCOMPARE(manager.searchLinks("github").size(), 1);
}

void TestLinkManager::testSearchMatchContext() {
    LinkManager manager;
    manager.addLink({"Name", "url", "", {"UrgentTask"}, "", "", ""});
    QCOMPARE(manager.searchLinks("Urgent").size(), 1);
}

void TestLinkManager::testSearchNoMatchReturnsEmpty() {
    LinkManager manager;
    manager.addLink({"Apple", "", "", {}, "", "", ""});
    QCOMPARE(manager.searchLinks("Banana").size(), 0);
}

void TestLinkManager::testSearchEmptyQueryReturnsAll() {
    LinkManager manager;
    manager.addLink({"L1", "", "", {}, "", "", ""});
    manager.addLink({"L2", "", "", {}, "", "", ""});
    QCOMPARE(manager.searchLinks("").size(), 2);
}

void TestLinkManager::testFilterByFolderExactMatch() {
    LinkManager manager;
    manager.addLink({"L1", "", "Work", {}, "", "", ""});
    manager.addLink({"L2", "", "Home", {}, "", "", ""});
    auto results = manager.filterLinks({"Work"}, {});
    QCOMPARE(results.size(), 1);
    QCOMPARE(QString::fromStdString(results[0].name), QString("L1"));
}

void TestLinkManager::testFilterByContextExactMatch() {
    LinkManager manager;
    manager.addLink({"L1", "", "", {"Fun"}, "", "", ""});
    manager.addLink({"L2", "", "", {"Work"}, "", "", ""});
    QCOMPARE(manager.filterLinks({}, {"Fun"}).size(), 1);
}

void TestLinkManager::testFilterByFolderAndContextCombination() {
    LinkManager manager;
    manager.addLink({"L1", "", "Work", {"Urgent"}, "", "", ""});
    manager.addLink({"L2", "", "Work", {"LowPriority"}, "", "", ""});
    auto results = manager.filterLinks({"Work"}, {"Urgent"});
    QCOMPARE(results.size(), 1);
    QCOMPARE(QString::fromStdString(results[0].name), QString("L1"));
}

void TestLinkManager::testFilterEmptyCriteriaReturnsAll() {
    LinkManager manager;
    manager.addLink({"L1", "", "Work", {}, "", "", ""});
    QCOMPARE(manager.filterLinks({}, {}).size(), 1);
}

void TestLinkManager::testFolderAddRemove() {
    LinkManager manager;
    manager.addFolder("Secret");
    QVERIFY(manager.hasFolder("Secret"));
    manager.removeFolder("Secret");
    QVERIFY(!manager.hasFolder("Secret"));
}

void TestLinkManager::testContextAddRemove() {
    LinkManager manager;
    manager.addContext("Hidden");
    QVERIFY(manager.hasContext("Hidden"));
    manager.removeContext("Hidden");
    QVERIFY(!manager.hasContext("Hidden"));
}

void TestLinkManager::testClearLinksFolderRemovesAssociation() {
    LinkManager manager;
    manager.addLink({"L1", "u", "ToDelete", {}, "", "", ""});
    manager.clearLinksFolder("ToDelete");
    QCOMPARE(QString::fromStdString(manager.getLinks()[0].folder), QString(""));
}
