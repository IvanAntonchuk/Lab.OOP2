/**
 * @file linkmanager.h
 * @brief Заголовочний файл для управління посиланнями.
 *
 * Містить визначення структури LinkData та класу LinkManager,
 * який відповідає за логіку роботи з колекцією посилань.
 */

#ifndef LINKMANAGER_H
#define LINKMANAGER_H

#include <string>
#include <vector>
#include <algorithm>

/**
 * @struct LinkData
 * @brief Структура для зберігання даних про одне посилання.
 */
struct LinkData {
    std::string name;       ///< @brief Назва посилання (заголовок).
    std::string url;        ///< @brief URL-адреса ресурсу.
    std::string folder;     ///< @brief Категорія (папка), до якої належить посилання.
    std::vector<std::string> contexts; ///< @brief Список контекстних тегів (наприклад, "Робота", "Навчання").
    std::string relatedUrl; ///< @brief Пов'язане посилання (якщо є).
    std::string comment;    ///< @brief Коментар користувача.
    std::string iconData;   ///< @brief Дані іконки сайту у форматі Base64 (PNG).
};

/**
 * @class LinkManager
 * @brief Клас для управління списком посилань.
 *
 * Забезпечує додавання, видалення, редагування, пошук та фільтрацію посилань,
 * а також управління папками та контекстами. Підтримує збереження та завантаження даних через SQLite.
 */
class LinkManager {
public:
    /**
     * @brief Конструктор за замовчуванням.
     * Ініціалізує менеджер та додає базові контексти.
     */
    LinkManager();

    /**
     * @brief Додає нове посилання до колекції.
     * @param newLink Об'єкт LinkData з даними нового посилання.
     */
    void addLink(const LinkData& newLink);

    /**
     * @brief Отримує список всіх посилань.
     * @return Посилання на константний вектор об'єктів LinkData.
     */
    const std::vector<LinkData>& getLinks() const;

    /**
     * @brief Видаляє посилання за індексом.
     * @param index Індекс посилання у списку (починаючи з 0).
     */
    void deleteLink(int index);

    /**
     * @brief Оновлює дані існуючого посилання.
     * @param index Індекс посилання, яке потрібно оновити.
     * @param updatedData Нові дані для посилання.
     */
    void updateLink(int index, const LinkData& updatedData);

    /**
     * @brief Шукає посилання за запитом.
     * Пошук здійснюється по назві, URL, коментарю, папці та контекстах.
     * @param query Рядок пошукового запиту.
     * @return Вектор знайдених посилань.
     */
    std::vector<LinkData> searchLinks(const std::string& query) const;

    /**
     * @brief Додає нову папку (категорію).
     * @param folderName Назва папки.
     */
    void addFolder(const std::string& folderName);

    /**
     * @brief Отримує список існуючих папок.
     * @return Константне посилання на вектор назв папок.
     */
    const std::vector<std::string>& getFolders() const;

    /**
     * @brief Видаляє папку зі списку.
     * @param folderName Назва папки для видалення.
     */
    void removeFolder(const std::string& folderName);

    /**
     * @brief Перевіряє наявність папки.
     * @param folderName Назва папки.
     * @return true, якщо папка існує, інакше false.
     */
    bool hasFolder(const std::string& folderName) const;

    /**
     * @brief Очищає прив'язку посилань до видаленої папки.
     * Встановлює поле folder у посиланнях в пустий рядок.
     * @param folderName Назва видаленої папки.
     */
    void clearLinksFolder(const std::string& folderName);

    /**
     * @brief Додає новий контекст (тег).
     * @param contextName Назва контексту.
     */
    void addContext(const std::string& contextName);

    /**
     * @brief Отримує список всіх контекстів.
     * @return Константне посилання на вектор назв контекстів.
     */
    const std::vector<std::string>& getContexts() const;

    /**
     * @brief Видаляє контекст зі списку.
     * @param contextName Назва контексту.
     */
    void removeContext(const std::string& contextName);

    /**
     * @brief Перевіряє існування контексту.
     * @param contextName Назва контексту.
     * @return true, якщо контекст існує.
     */
    bool hasContext(const std::string& contextName) const;

    /**
     * @brief Зберігає дані у базу даних SQLite.
     * @param filePath Залишено порожнім для сумісності з попередніми версіями API.
     * @return true у разі успіху, інакше false.
     */
    bool saveToFile(const std::string& filePath = "");

    /**
     * @brief Завантажує дані з бази даних SQLite.
     * @param filePath Залишено порожнім для сумісності з попередніми версіями API.
     * @return true у разі успіху, інакше false.
     */
    bool loadFromFile(const std::string& filePath = "");

    /**
     * @brief Фільтрує посилання за папками та контекстами.
     * @param allowedFolders Список дозволених папок.
     * @param allowedContexts Список дозволених контекстів.
     * @return Вектор посилань, що відповідають критеріям.
     */
    std::vector<LinkData> filterLinks(const std::vector<std::string>& allowedFolders, const std::vector<std::string>& allowedContexts) const;

private:
    std::vector<LinkData> m_links;      ///< Список всіх посилань.
    std::vector<std::string> m_folders; ///< Список доступних папок.
    std::vector<std::string> m_contexts;///< Список доступних контекстів.
};

#endif // LINKMANAGER_H
