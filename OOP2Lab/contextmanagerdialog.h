#ifndef CONTEXTMANAGERDIALOG_H
#define CONTEXTMANAGERDIALOG_H

#include <QDialog>
#include "linkmanager.h"

namespace Ui {
class ContextManagerDialog;
}

class ContextManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContextManagerDialog(LinkManager* manager, QWidget *parent = nullptr);
    ~ContextManagerDialog();

private slots:
    void on_createContextButton_clicked();
    void on_deleteContextButton_clicked();

    void on_deselectButton_clicked();

private:
    void loadContextsToTree();

    Ui::ContextManagerDialog *ui;
    LinkManager* m_manager;
};

#endif // CONTEXTMANAGERDIALOG_H
