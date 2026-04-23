#ifndef TESTLINKMANAGER_H
#define TESTLINKMANAGER_H

#include <QObject>
#include <QtTest>

class TestLinkManager : public QObject {
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();

    void testAddLinkBasic();
    void testAddLinkEmptyData();
    void testAddLinkDuplicateContexts();
    void testDeleteLinkValidIndex();
    void testDeleteLinkInvalidIndexBounds();
    void testDeleteLinkEmptyManager();
    void testUpdateLinkValid();
    void testUpdateLinkCreatesNewFolders();

    void testSearchMatchName();
    void testSearchMatchUrl();
    void testSearchMatchContext();
    void testSearchNoMatchReturnsEmpty();
    void testSearchEmptyQueryReturnsAll();

    void testFilterByFolderExactMatch();
    void testFilterByContextExactMatch();
    void testFilterByFolderAndContextCombination();
    void testFilterEmptyCriteriaReturnsAll();

    void testFolderAddRemove();
    void testContextAddRemove();
    void testClearLinksFolderRemovesAssociation();
};
#endif // TESTLINKMANAGER_H
