#ifndef ADDLINKDIALOG_H
#define ADDLINKDIALOG_H

#include <QDialog>
#include "linkmanager.h"

namespace Ui {
class AddLinkDialog;
}

/**
 * @brief Клас AddLinkDialog відповідає за графічний інтерфейс додавання та редагування посилань.
 * * Цей діалог надає користувачеві форму для введення або зміни даних про посилання,
 * включаючи URL-адресу, назву, папку, контекст та додатковий коментар.
 */
class AddLinkDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класу AddLinkDialog.
     * @param parent Вказівник на батьківський віджет (за замовчуванням nullptr).
     */
    explicit AddLinkDialog(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класу AddLinkDialog.
     * Звільняє ресурси, виділені під графічний інтерфейс.
     */
    ~AddLinkDialog();

    /**
     * @brief Отримує дані про посилання, введені користувачем у форму.
     * @return Об'єкт LinkData, що містить поточні значення полів діалогу.
     */
    LinkData getLinkData() const;

    /**
     * @brief Заповнює поля діалогу даними з існуючого посилання (використовується для редагування).
     * @param data Об'єкт LinkData, дані якого будуть відображені у формі.
     */
    void setLinkData(const LinkData& data);

    /**
     * @brief Встановлює список доступних папок у випадаючий список діалогу.
     * @param folders Вектор рядків із назвами існуючих папок.
     */
    void setFolders(const std::vector<std::string>& folders);

    /**
     * @brief Встановлює список доступних контекстів у випадаючий список діалогу.
     * @param contexts Вектор рядків із назвами існуючих контекстів.
     */
    void setContexts(const std::vector<std::string>& contexts);

private slots:
    /**
     * @brief Слот, що викликається при натисканні кнопки "Fetch Title".
     * Автоматично завантажує сторінку за введеним URL та намагається отримати її заголовок (<title>).
     */
    void on_fetchTitleButton_clicked();

private:
    /**
     * @brief Вказівник на об'єкт згенерованого графічного інтерфейсу.
     */
    Ui::AddLinkDialog *ui;
};

#endif // ADDLINKDIALOG_H
