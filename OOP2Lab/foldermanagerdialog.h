#ifndef FOLDERMANAGERDIALOG_H
#define FOLDERMANAGERDIALOG_H

#include <QDialog>
#include "linkmanager.h"

namespace Ui {
class FolderManagerDialog;
}

class FolderManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FolderManagerDialog(LinkManager* manager, QWidget *parent = nullptr);
    ~FolderManagerDialog();

private slots:
    void on_createFolderButton_clicked();
    void on_deleteFolderButton_clicked();
    void on_deselectButton_clicked();

private:
    void loadFoldersToTree();

    Ui::FolderManagerDialog *ui;
    LinkManager* m_manager;
};

#endif // FOLDERMANAGERDIALOG_H
