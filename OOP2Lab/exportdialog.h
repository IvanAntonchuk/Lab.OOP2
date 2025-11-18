#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include "linkmanager.h"

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = nullptr);
    ~ExportDialog();
    void setLinks(const std::vector<LinkData>& links);
private slots:
    void on_generateButton_clicked();
    void on_closeButton_clicked();
private:
    Ui::ExportDialog *ui;
    std::vector<LinkData> m_dataToExport;
};

#endif // EXPORTDIALOG_H
