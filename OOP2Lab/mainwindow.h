#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <memory>

#include "addlinkdialog.h"
#include "linkmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainController;

/**
 * @brief Клас MainWindow є головним вікном програми і виступає Представленням (View) у патерні MVC.
 * * Відповідає за відображення графічного інтерфейсу користувача (GUI), прийом вводу
 * (натискання кнопок, введення тексту, перетягування файлів) та делегування обробки
 * цих подій Контролеру (MainController). Не містить бізнес-логіки.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор головного вікна.
     * Ініціалізує UI та створює екземпляр MainController для керування логікою.
     * @param parent Вказівник на батьківський віджет (за замовчуванням nullptr).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор головного вікна.
     * Очищає виділені ресурси графічного інтерфейсу.
     */
    ~MainWindow();

    /**
     * @brief Оновлює таблицю посилань на екрані.
     * Викликається Контролером для передачі нових або відфільтрованих даних у View.
     * @param links Вектор об'єктів LinkData, які потрібно відобразити в QTableWidget.
     */
    void updateTable(const std::vector<LinkData>& links);

private slots:
    /** @brief Відкриває діалог для додавання нового посилання. */
    void on_addButton_clicked();

    /** @brief Видаляє вибране в таблиці посилання (передає команду в Контролер). */
    void on_deleteButton_clicked();

    /** @brief Відкриває діалог для редагування вибраного посилання. */
    void on_editButton_clicked();

    /** @brief Ініціює пошук посилань при натисканні кнопки пошуку. */
    void on_searchButton_clicked();

    /** * @brief Динамічно фільтрує таблицю під час введення тексту в поле пошуку.
     * @param arg1 Поточний введений текст.
     */
    void on_searchLineEdit_textChanged(const QString &arg1);

    /** * @brief Відкриває посилання у стандартному веб-браузері при подвійному кліку по комірці.
     * @param row Рядок клікнутої комірки.
     * @param column Стовпець клікнутої комірки.
     */
    void on_linksTableWidget_cellDoubleClicked(int row, int column);

    /** @brief Відкриває діалог експорту посилань у різні формати (CSV, HTML). */
    void on_exportButton_clicked();

    /** @brief Відкриває діалог для управління папками (створення/видалення). */
    void on_manageFoldersButton_clicked();

    /** @brief Відкриває діалог для управління контекстними тегами. */
    void on_manageContextsButton_clicked();

    /** @brief Відкриває діалог для налаштування фільтрів за папками та контекстами. */
    void on_filterButton_clicked();

    /** @brief Виконує пошук введеного тексту в інтернеті через зовнішню пошукову систему. */
    void on_searchOnlineButton_clicked();

    /** @brief Обробляє дію "Зберегти як" з верхнього меню. */
    void on_actionSaveAs_triggered();

    /** @brief Відкриває діалогове вікно для вибору файлу та імпорту даних у програму. */
    void on_importButton_clicked();

    /** @brief Генерує та відображає QR-код для вибраного в таблиці посилання. */
    void on_qrCodeButton_clicked();

private:
    Ui::MainWindow *ui; ///< Вказівник на згенерований клас інтерфейсу.

    std::unique_ptr<MainController> m_controller; ///< Вказівник на Контролер, що керує цим вікном (MVC).

    std::vector<std::string> m_checkedFolders;  ///< Збережений стан вибраних папок для фільтрації.
    std::vector<std::string> m_checkedContexts; ///< Збережений стан вибраних контекстів для фільтрації.
    bool m_isFilterInitialized;                 ///< Прапорець, що вказує, чи були фільтри вже налаштовані.

protected:
    /**
     * @brief Перехоплює подію закриття вікна.
     * Може використовуватися для підтвердження виходу або збереження налаштувань.
     * @param event Об'єкт події закриття.
     */
    void closeEvent(QCloseEvent *event) override;

    /**
     * @brief Обробляє подію входження об'єкта (Drag) у зону вікна.
     * Перевіряє, чи містить перетягуваний об'єкт допустимі дані (наприклад, URL або текст).
     * @param event Об'єкт події DragEnter.
     */
    void dragEnterEvent(QDragEnterEvent *event) override;

    /**
     * @brief Обробляє подію скидання об'єкта (Drop) у вікно.
     * Витягує дані з перетягнутого об'єкта та ініціює додавання нового посилання.
     * @param event Об'єкт події Drop.
     */
    void dropEvent(QDropEvent *event) override;
};
#endif // MAINWINDOW_H
