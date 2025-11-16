#ifndef ADDLINKDIALOG_H
#define ADDLINKDIALOG_H

#include <QDialog>
#include "linkmanager.h"

namespace Ui {
class AddLinkDialog;
}

class AddLinkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLinkDialog(QWidget *parent = nullptr);
    ~AddLinkDialog();
    LinkData getLinkData() const;

private:
    Ui::AddLinkDialog *ui;
};

#endif // ADDLINKDIALOG_H
