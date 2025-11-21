#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "addlinkdialog.h"
#include "linkmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_editButton_clicked();
    void on_searchButton_clicked();
    void on_searchLineEdit_textChanged(const QString &arg1);
    void on_linksTableWidget_cellDoubleClicked(int row, int column);
    void on_exportButton_clicked();
    void on_manageFoldersButton_clicked();

    void on_manageContextsButton_clicked();

    void on_filterButton_clicked();

private:
    Ui::MainWindow *ui;
    LinkManager m_linkManager;
    QString m_saveFilePath;
    void updateTable(const std::vector<LinkData>& links);
    std::vector<std::string> m_checkedFolders;
    std::vector<std::string> m_checkedContexts;
    bool m_isFilterInitialized;
protected:
    void closeEvent(QCloseEvent *event) override;

};
#endif // MAINWINDOW_H
