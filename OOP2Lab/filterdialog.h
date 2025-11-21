#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include "linkmanager.h"

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterDialog(LinkManager* manager, QWidget *parent = nullptr);
    ~FilterDialog();
    std::vector<std::string> getSelectedFolders() const;
    std::vector<std::string> getSelectedContexts() const;
    void setSelection(const std::vector<std::string>& folders, const std::vector<std::string>& contexts);

private:
    void loadData();
    Ui::FilterDialog *ui;
    LinkManager* m_manager;
};

#endif // FILTERDIALOG_H
