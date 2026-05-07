#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "linkmanager.h"
#include <QString>
#include <vector>
#include <string>

class MainWindow;

/**
 * @brief Клас MainController є Контролером (Controller) у патерні MVC.
 * * Він слугує проміжним шаром між графічним інтерфейсом (MainWindow - View)
 * та бізнес-логікою (LinkManager - Model). Контролер приймає дії користувача від View,
 * передає їх у Model для обробки, а потім оновлює View відповідними результатами.
 */
class MainController {
public:
    /**
     * @brief Конструктор класу MainController.
     * @param view Вказівник на головне вікно програми (View), яким керуватиме цей контролер.
     */
    MainController(MainWindow* view);

    /**
     * @brief Деструктор класу MainController.
     */
    ~MainController();

    /**
     * @brief Ініціалізує початковий стан програми.
     * Завантажує дані з бази даних через LinkManager та ініціює первинне відображення
     * списку посилань у MainWindow.
     */
    void initialize();

    /**
     * @brief Передає команду на додавання нового посилання до моделі.
     * Після успішного додавання в базу, автоматично оновлює відображення у View.
     * @param data Об'єкт LinkData з даними нового посилання.
     */
    void addLink(const LinkData& data);

    /**
     * @brief Передає команду на видалення посилання до моделі.
     * Після видалення оновлює відображення списку у View.
     * @param index Індекс посилання, яке потрібно видалити.
     */
    void deleteLink(int index);

    /**
     * @brief Передає команду на оновлення (редагування) існуючого посилання до моделі.
     * Оновлює список у графічному інтерфейсі після збереження змін.
     * @param index Індекс посилання, яке редагується.
     * @param data Об'єкт LinkData з оновленими даними.
     */
    void updateLink(int index, const LinkData& data);

    /**
     * @brief Виконує пошук посилань через модель та передає результати у View.
     * @param query Рядок пошукового запиту.
     */
    void searchLinks(const std::string& query);

    /**
     * @brief Виконує фільтрацію посилань через модель та передає результати у View.
     * @param folders Вектор дозволених для відображення папок.
     * @param contexts Вектор дозволених для відображення контекстів.
     */
    void filterLinks(const std::vector<std::string>& folders, const std::vector<std::string>& contexts);

    /**
     * @brief Отримує список усіх доступних папок із моделі.
     * @return Вектор рядків із назвами папок.
     */
    std::vector<std::string> getFolders() const;

    /**
     * @brief Отримує список усіх доступних контекстів із моделі.
     * @return Вектор рядків із назвами контекстів.
     */
    std::vector<std::string> getContexts() const;

    /**
     * @brief Отримує повний список посилань із моделі.
     * @return Константне посилання на вектор об'єктів LinkData.
     */
    const std::vector<LinkData>& getAllLinks() const;

    /**
     * @brief Надає прямий доступ до об'єкта LinkManager.
     * Використовується для передачі моделі у діалогові вікна (наприклад, FilterDialog або FolderManagerDialog),
     * яким потрібен безпосередній доступ до бізнес-логіки.
     * @return Вказівник на екземпляр LinkManager.
     */
    LinkManager* getLinkManager();

private:
    /**
     * @brief Вказівник на графічний інтерфейс (View).
     */
    MainWindow* m_view;

    /**
     * @brief Екземпляр головної моделі (Model), яка керує даними.
     */
    LinkManager m_linkManager;

    /**
     * @brief Шлях до файлу або бази даних для збереження інформації.
     */
    QString m_saveFilePath;
};

#endif // MAINCONTROLLER_H
