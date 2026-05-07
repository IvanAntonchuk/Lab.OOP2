#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include "linkmanager.h"

namespace Ui {
class ExportDialog;
}

/**
 * @brief Клас ExportDialog відповідає за графічний інтерфейс експорту посилань.
 * * Цей діалог дозволяє користувачеві вибрати формат експорту (наприклад, CSV або HTML)
 * та зберегти вибрані або всі наявні посилання у відповідний файл.
 */
class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класу ExportDialog.
     * @param parent Вказівник на батьківський віджет (за замовчуванням nullptr).
     */
    explicit ExportDialog(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класу ExportDialog.
     * Звільняє ресурси, виділені під графічний інтерфейс.
     */
    ~ExportDialog();

    /**
     * @brief Встановлює список посилань, які будуть доступні для експорту.
     * @param links Вектор об'єктів LinkData, які планується експортувати.
     */
    void setLinks(const std::vector<LinkData>& links);

private slots:
    /**
     * @brief Слот, що викликається при натисканні кнопки "Generate" (або "Export").
     * Запускає процес експорту даних у вибраний користувачем формат,
     * використовуючи відповідну стратегію експорту.
     */
    void on_generateButton_clicked();

    /**
     * @brief Слот, що викликається при натисканні кнопки "Close".
     * Закриває вікно діалогу без виконання експорту.
     */
    void on_closeButton_clicked();

private:
    /**
     * @brief Вказівник на об'єкт згенерованого графічного інтерфейсу.
     */
    Ui::ExportDialog *ui;

    /**
     * @brief Контейнер для зберігання посилань, які були передані для експорту.
     */
    std::vector<LinkData> m_dataToExport;
};

#endif // EXPORTDIALOG_H
