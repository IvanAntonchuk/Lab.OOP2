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

private:
    Ui::MainWindow *ui;
    LinkManager m_linkManager;
    QString m_saveFilePath;
    void saveLinksToFile();
    void loadLinksFromFile();
    void updateTable(const std::vector<LinkData>& links);
protected:
    void closeEvent(QCloseEvent *event) override;

};
#endif // MAINWINDOW_H
