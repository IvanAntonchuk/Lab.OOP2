#ifndef FOLDERMANAGERDIALOG_H
#define FOLDERMANAGERDIALOG_H

#include <QDialog>
#include "linkmanager.h"

namespace Ui {
class FolderManagerDialog;
}

/**
 * @brief Клас FolderManagerDialog відповідає за графічний інтерфейс управління папками.
 * * Цей діалог дозволяє користувачеві переглядати ієрархію або список існуючих папок,
 * створювати нові папки та видаляти непотрібні. Взаємодіє з основним менеджером посилань
 * для збереження змін у базі даних.
 */
class FolderManagerDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класу FolderManagerDialog.
     * @param manager Вказівник на об'єкт LinkManager для доступу до даних та виконання операцій з папками.
     * @param parent Вказівник на батьківський віджет (за замовчуванням nullptr).
     */
    explicit FolderManagerDialog(LinkManager* manager, QWidget *parent = nullptr);

    /**
     * @brief Деструктор класу FolderManagerDialog.
     * Звільняє ресурси, виділені під графічний інтерфейс.
     */
    ~FolderManagerDialog();

private slots:
    /**
     * @brief Слот, що викликається при натисканні кнопки "Створити папку" (Create Folder).
     * Зчитує введену назву та додає нову папку до системи через LinkManager.
     */
    void on_createFolderButton_clicked();

    /**
     * @brief Слот, що викликається при натисканні кнопки "Видалити папку" (Delete Folder).
     * Видаляє вибрану в списку/дереві папку.
     */
    void on_deleteFolderButton_clicked();

    /**
     * @brief Слот, що викликається при натисканні кнопки "Зняти виділення" (Deselect).
     * Знімає фокус/виділення з поточного вибраного елемента у дереві папок.
     */
    void on_deselectButton_clicked();

private:
    /**
     * @brief Завантажує список папок із LinkManager та відображає їх у графічному дереві (QTreeView/QTreeWidget).
     * Викликається при ініціалізації діалогу та після кожної зміни (створення/видалення папки) для оновлення інтерфейсу.
     */
    void loadFoldersToTree();

    /**
     * @brief Вказівник на об'єкт згенерованого графічного інтерфейсу.
     */
    Ui::FolderManagerDialog *ui;

    /**
     * @brief Вказівник на менеджер посилань, який містить бізнес-логіку роботи з папками.
     */
    LinkManager* m_manager;
};

#endif // FOLDERMANAGERDIALOG_H
