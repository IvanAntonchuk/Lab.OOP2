#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include "linkmanager.h"

namespace Ui {
class FilterDialog;
}

/**
 * @brief Клас FilterDialog відповідає за графічний інтерфейс фільтрації посилань.
 * * Цей діалог дозволяє користувачеві вибирати конкретні папки та контексти,
 * щоб відображати у головному вікні лише ті посилання, які відповідають вибраним критеріям.
 */
class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класу FilterDialog.
     * @param manager Вказівник на об'єкт LinkManager для отримання доступних у базі папок та контекстів.
     * @param parent Вказівник на батьківський віджет (за замовчуванням nullptr).
     */
    explicit FilterDialog(LinkManager* manager, QWidget *parent = nullptr);

    /**
     * @brief Деструктор класу FilterDialog.
     * Звільняє ресурси, виділені під графічний інтерфейс.
     */
    ~FilterDialog();

    /**
     * @brief Отримує список папок, які користувач виділив для фільтрації.
     * @return Вектор рядків із назвами вибраних папок.
     */
    std::vector<std::string> getSelectedFolders() const;

    /**
     * @brief Отримує список контекстів, які користувач виділив для фільтрації.
     * @return Вектор рядків із назвами вибраних контекстів.
     */
    std::vector<std::string> getSelectedContexts() const;

    /**
     * @brief Відновлює попередній вибір користувача у вікні діалогу.
     * Використовується для того, щоб при повторному відкритті фільтра зберігалися раніше встановлені прапорці.
     * @param folders Вектор назв папок, які мають бути позначені як вибрані.
     * @param contexts Вектор назв контекстів, які мають бути позначені як вибрані.
     */
    void setSelection(const std::vector<std::string>& folders, const std::vector<std::string>& contexts);

private:
    /**
     * @brief Завантажує доступні папки та контексти з об'єкта LinkManager.
     * Ініціалізує елементи графічного інтерфейсу (наприклад, списки або прапорці) на основі наявних даних.
     */
    void loadData();

    /**
     * @brief Вказівник на об'єкт згенерованого графічного інтерфейсу.
     */
    Ui::FilterDialog *ui;

    /**
     * @brief Вказівник на менеджер посилань, звідки отримуються унікальні папки та контексти.
     */
    LinkManager* m_manager;
};

#endif // FILTERDIALOG_H
