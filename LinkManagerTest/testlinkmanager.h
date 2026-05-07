/**
 * @file testlinkmanager.h
 * @brief Заголовочний файл для модульного тестування основної бізнес-логіки (LinkManager).
 */

#ifndef TESTLINKMANAGER_H
#define TESTLINKMANAGER_H

#include <QObject>
#include <QtTest>

/**
 * @class TestLinkManager
 * @brief Клас модульних тестів для перевірки головної моделі LinkManager.
 *
 * Використовує фреймворк QtTest для комплексного тестування всіх операцій CRUD
 * (створення, читання, оновлення, видалення) з посиланнями, а також логіки
 * пошуку, фільтрації та управління категоріями (папками і контекстами).
 */
class TestLinkManager : public QObject {
    Q_OBJECT
private slots:
    /**
     * @brief Глобальна ініціалізація тестового набору.
     * Викликається один раз перед початком виконання всіх тестів у цьому класі.
     */
    void initTestCase();

    /**
     * @brief Глобальне очищення після тестового набору.
     * Викликається один раз після завершення всіх тестів.
     */
    void cleanupTestCase();

    /**
     * @brief Підготовка середовища перед кожним окремим тестом.
     * Забезпечує ізоляцію тестів один від одного (наприклад, очищає базу даних
     * або перестворює об'єкт LinkManager), щоб результати одного тесту не впливали на інший.
     */
    void init();

    /** @brief Перевіряє коректне додавання базового посилання з усіма полями. */
    void testAddLinkBasic();

    /** @brief Перевіряє поведінку менеджера при спробі додати посилання з порожніми даними. */
    void testAddLinkEmptyData();

    /** @brief Перевіряє, чи коректно обробляються (або ігноруються) дублюючі контексти при додаванні. */
    void testAddLinkDuplicateContexts();

    /** @brief Перевіряє успішне видалення існуючого посилання за коректним індексом. */
    void testDeleteLinkValidIndex();

    /** @brief Перевіряє захист від виходу за межі масиву (видалення за від'ємним індексом або індексом > size). */
    void testDeleteLinkInvalidIndexBounds();

    /** @brief Перевіряє поведінку при спробі видалити елемент з порожнього списку посилань. */
    void testDeleteLinkEmptyManager();

    /** @brief Перевіряє успішне оновлення даних існуючого посилання. */
    void testUpdateLinkValid();

    /** @brief Перевіряє, чи автоматично створюються нові папки/контексти, якщо вони вказані при оновленні посилання. */
    void testUpdateLinkCreatesNewFolders();

    /** @brief Перевіряє, чи знаходить пошук посилання за частковим або повним збігом у назві. */
    void testSearchMatchName();

    /** @brief Перевіряє, чи працює пошук по URL-адресі. */
    void testSearchMatchUrl();

    /** @brief Перевіряє пошук за наявністю певного контексту (тегу). */
    void testSearchMatchContext();

    /** @brief Перевіряє, що при відсутності збігів повертається порожній вектор. */
    void testSearchNoMatchReturnsEmpty();

    /** @brief Перевіряє, що порожній пошуковий запит повертає повний список посилань. */
    void testSearchEmptyQueryReturnsAll();

    /** @brief Перевіряє точне відфільтровування посилань за вказаною папкою. */
    void testFilterByFolderExactMatch();

    /** @brief Перевіряє точне відфільтровування посилань за вказаним контекстом. */
    void testFilterByContextExactMatch();

    /** @brief Перевіряє фільтрацію при одночасному застосуванні критеріїв папки та контексту. */
    void testFilterByFolderAndContextCombination();

    /** @brief Перевіряє, що відсутність вибраних фільтрів призводить до повернення всіх посилань. */
    void testFilterEmptyCriteriaReturnsAll();

    /** @brief Перевіряє функціонал додавання нових та видалення існуючих папок. */
    void testFolderAddRemove();

    /** @brief Перевіряє функціонал додавання нових та видалення існуючих контекстів. */
    void testContextAddRemove();

    /** @brief Перевіряє, що при видаленні папки, усі посилання, які їй належали, втрачають цю прив'язку (поле folder стає порожнім). */
    void testClearLinksFolderRemovesAssociation();
};
#endif // TESTLINKMANAGER_H
