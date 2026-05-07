/**
 * @file linkmanager.h
 * @brief Заголовочний файл для управління посиланнями.
 *
 * Містить визначення структури LinkData та класу LinkManager,
 * який виступає головною моделлю (Model) у патерні MVC і відповідає
 * за бізнес-логіку роботи з колекцією посилань.
 */

#ifndef LINKMANAGER_H
#define LINKMANAGER_H

#include <string>
#include <vector>
#include <algorithm>

/**
 * @struct LinkData
 * @brief Структура (Data Transfer Object) для зберігання даних про одне посилання.
 */
struct LinkData {
    std::string name;       ///< @brief Назва посилання (заголовок сторінки).
    std::string url;        ///< @brief URL-адреса веб-ресурсу.
    std::string folder;     ///< @brief Категорія (папка), до якої належить посилання.
    std::vector<std::string> contexts; ///< @brief Список контекстних тегів (наприклад, "Робота", "Навчання").
    std::string relatedUrl; ///< @brief Пов'язане посилання (додатковий ресурс, якщо є).
    std::string comment;    ///< @brief Текстовий коментар користувача.
    std::string iconData;   ///< @brief Дані фавіконки (favicon) сайту у форматі Base64 (PNG).
};

/**
 * @class LinkManager
 * @brief Головний клас-менеджер для управління списком посилань.
 *
 * Відповідає за додавання, видалення, редагування, пошук та фільтрацію посилань,
 * а також управління ієрархією папок та контекстами.
 * У поточній версії архітектури делегує операції постійного зберігання (persistence)
 * класу DatabaseManager, забезпечуючи надійну роботу через SQLite.
 */
class LinkManager {
public:
    /**
     * @brief Конструктор за замовчуванням.
     * Ініціалізує менеджер порожніми масивами та додає базові/стандартні контексти.
     */
    LinkManager();

    /**
     * @brief Додає нове посилання до колекції в оперативній пам'яті.
     * @param newLink Об'єкт LinkData з даними нового посилання.
     */
    void addLink(const LinkData& newLink);

    /**
     * @brief Отримує список усіх поточних посилань.
     * @return Константне посилання на вектор об'єктів LinkData.
     */
    const std::vector<LinkData>& getLinks() const;

    /**
     * @brief Видаляє посилання за його індексом у масиві.
     * @param index Індекс посилання у списку (починаючи з 0).
     */
    void deleteLink(int index);

    /**
     * @brief Оновлює дані існуючого посилання.
     * @param index Індекс посилання, яке потрібно відредагувати.
     * @param updatedData Об'єкт LinkData з новими даними.
     */
    void updateLink(int index, const LinkData& updatedData);

    /**
     * @brief Виконує наскрізний пошук посилань за текстовим запитом.
     * Пошук є нечутливим до регістру та здійснюється по назві, URL, коментарю, папці та контекстах.
     * @param query Текстовий рядок пошукового запиту.
     * @return Вектор посилань, що містять шуканий текст.
     */
    std::vector<LinkData> searchLinks(const std::string& query) const;

    /**
     * @brief Додає нову папку (категорію) до системи.
     * @param folderName Назва нової папки.
     */
    void addFolder(const std::string& folderName);

    /**
     * @brief Отримує список усіх існуючих папок.
     * @return Константне посилання на вектор рядків із назвами папок.
     */
    const std::vector<std::string>& getFolders() const;

    /**
     * @brief Видаляє папку зі списку доступних категорій.
     * @param folderName Назва папки для видалення.
     */
    void removeFolder(const std::string& folderName);

    /**
     * @brief Перевіряє, чи існує папка з такою назвою.
     * @param folderName Назва папки для перевірки.
     * @return true, якщо папка знайдена, інакше false.
     */
    bool hasFolder(const std::string& folderName) const;

    /**
     * @brief Очищає прив'язку посилань до видаленої папки.
     * Проходить по всіх посиланнях і встановлює поле folder у порожній рядок ("")
     * для тих, які належали до видаленої категорії.
     * @param folderName Назва видаленої папки.
     */
    void clearLinksFolder(const std::string& folderName);

    /**
     * @brief Додає новий контекст (тег) до системи.
     * @param contextName Назва нового контексту.
     */
    void addContext(const std::string& contextName);

    /**
     * @brief Отримує список усіх доступних контекстів.
     * @return Константне посилання на вектор рядків із назвами контекстів.
     */
    const std::vector<std::string>& getContexts() const;

    /**
     * @brief Видаляє контекст зі списку.
     * @param contextName Назва контексту для видалення.
     */
    void removeContext(const std::string& contextName);

    /**
     * @brief Перевіряє, чи існує контекст із такою назвою.
     * @param contextName Назва контексту для перевірки.
     * @return true, якщо контекст знайдено, інакше false.
     */
    bool hasContext(const std::string& contextName) const;

    /**
     * @brief Зберігає всі поточні дані у базу даних SQLite.
     * Делегує операцію збереження класу DatabaseManager.
     * Назва методу збережена для зворотної сумісності зі старим API, яке працювало з файлами.
     * @param filePath Застарілий параметр, залишено порожнім для сумісності.
     * @return true, якщо транзакція запису в БД пройшла успішно, інакше false.
     */
    bool saveToFile(const std::string& filePath = "");

    /**
     * @brief Завантажує всі дані з бази даних SQLite в оперативну пам'ять.
     * Делегує операцію читання класу DatabaseManager.
     * Назва методу збережена для зворотної сумісності зі старим API.
     * @param filePath Застарілий параметр, залишено порожнім для сумісності.
     * @return true, якщо дані успішно прочитані з БД, інакше false.
     */
    bool loadFromFile(const std::string& filePath = "");

    /**
     * @brief Фільтрує посилання за вибраними папками та контекстами.
     * @param allowedFolders Вектор назв папок, які дозволено відображати.
     * @param allowedContexts Вектор назв контекстів, які дозволено відображати.
     * @return Вектор посилань, що відповідають хоча б одному з вибраних критеріїв.
     */
    std::vector<LinkData> filterLinks(const std::vector<std::string>& allowedFolders, const std::vector<std::string>& allowedContexts) const;

private:
    std::vector<LinkData> m_links;      ///< Внутрішній масив усіх посилань.
    std::vector<std::string> m_folders; ///< Внутрішній масив доступних папок.
    std::vector<std::string> m_contexts;///< Внутрішній масив доступних контекстів.
};

#endif // LINKMANAGER_H
