/**
 * @file contextmanagerdialog.h
 * @brief Заголовочний файл діалогового вікна для управління контекстами (тегами).
 */

#ifndef CONTEXTMANAGERDIALOG_H
#define CONTEXTMANAGERDIALOG_H

#include <QDialog>
#include "linkmanager.h"

namespace Ui {
class ContextManagerDialog;
}

/**
 * @class ContextManagerDialog
 * @brief Діалогове вікно для додавання та видалення користувацьких контекстів.
 */
class ContextManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContextManagerDialog(LinkManager* manager, QWidget *parent = nullptr);
    ~ContextManagerDialog();

private slots:
    void on_addContextButton_clicked();
    void on_deleteContextButton_clicked();

private:
    Ui::ContextManagerDialog *ui;
    LinkManager* m_manager;

    void loadContexts();
};

#endif // CONTEXTMANAGERDIALOG_H
