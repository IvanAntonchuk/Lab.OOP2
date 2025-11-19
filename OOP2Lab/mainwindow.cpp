#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "exportdialog.h"

#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir dir(configPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    m_saveFilePath = configPath + "/links.json";
    m_linkManager.loadFromFile(m_saveFilePath.toStdString());
    updateTable(m_linkManager.getLinks());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    AddLinkDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted)
    {
        LinkData newData = dialog.getLinkData();

        m_linkManager.addLink(newData);
        updateTable(m_linkManager.getLinks());
    }
}

void MainWindow::updateTable(const std::vector<LinkData>& links)
{
    ui->linksTableWidget->clearContents();
    ui->linksTableWidget->setRowCount(0);

    if (ui->linksTableWidget->columnCount() < 4) {
        ui->linksTableWidget->setColumnCount(4);
        ui->linksTableWidget->setHorizontalHeaderLabels({"Назва", "URL", "Контекст", "Коментар"});
    }

    for (const LinkData& link : links)
    {
        int newRow = ui->linksTableWidget->rowCount();
        ui->linksTableWidget->insertRow(newRow);

        ui->linksTableWidget->setItem(newRow, 0, new QTableWidgetItem(QString::fromStdString(link.name)));
        ui->linksTableWidget->setItem(newRow, 1, new QTableWidgetItem(QString::fromStdString(link.url)));
        ui->linksTableWidget->setItem(newRow, 2, new QTableWidgetItem(QString::fromStdString(link.context)));
        ui->linksTableWidget->setItem(newRow, 3, new QTableWidgetItem(QString::fromStdString(link.comment)));
    }

    ui->linksTableWidget->resizeColumnsToContents();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_linkManager.saveToFile(m_saveFilePath.toStdString());
    event->accept();
}


void MainWindow::on_deleteButton_clicked()
{
    int selectedRow = ui->linksTableWidget->currentRow();
    if (selectedRow < 0)
    {
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження видалення", "Ви справді хочете видалити це посилання?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        m_linkManager.deleteLink(selectedRow);
        updateTable(m_linkManager.getLinks());
    }
}

void MainWindow::on_editButton_clicked()
{
    int selectedRow = ui->linksTableWidget->currentRow();
    if (selectedRow < 0)
    {
        return;
    }
    LinkData currentData = m_linkManager.getLinks()[selectedRow];
    AddLinkDialog dialog(this);
    dialog.setLinkData(currentData);

    if (dialog.exec() == QDialog::Accepted)
    {
        LinkData updatedData = dialog.getLinkData();

        m_linkManager.updateLink(selectedRow, updatedData);

        updateTable(m_linkManager.getLinks());
    }
}


void MainWindow::on_searchButton_clicked()
{
    std::string query = ui->searchLineEdit->text().toStdString();
    std::vector<LinkData> searchResults = m_linkManager.searchLinks(query);
    updateTable(searchResults);
}


void MainWindow::on_searchLineEdit_textChanged(const QString &arg1)
{
    on_searchButton_clicked();
}


void MainWindow::on_linksTableWidget_cellDoubleClicked(int row, int column)
{
    QString urlString = ui->linksTableWidget->item(row, 1)->text();
    QDesktopServices::openUrl(QUrl(urlString));
}


void MainWindow::on_exportButton_clicked()
{
    ExportDialog dialog(this);
    dialog.setLinks(m_linkManager.getLinks());

    dialog.exec();
}


