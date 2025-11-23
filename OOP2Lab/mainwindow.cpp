#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "exportdialog.h"
#include "foldermanagerdialog.h"
#include "contextmanagerdialog.h"
#include "filterdialog.h"

#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->linksTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir dir(configPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    m_saveFilePath = configPath + "/links.json";
    m_isFilterInitialized = false;
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
    dialog.setFolders(m_linkManager.getFolders());
    dialog.setContexts(m_linkManager.getContexts());

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
    if (ui->linksTableWidget->columnCount() < 5) {
        ui->linksTableWidget->setColumnCount(5);
        ui->linksTableWidget->setHorizontalHeaderLabels({"Назва", "URL", "Папка", "Контекст", "Коментар"});
    }

    for (const LinkData& link : links)
    {
        int newRow = ui->linksTableWidget->rowCount();
        ui->linksTableWidget->insertRow(newRow);
        ui->linksTableWidget->setItem(newRow, 0, new QTableWidgetItem(QString::fromStdString(link.name)));
        ui->linksTableWidget->setItem(newRow, 1, new QTableWidgetItem(QString::fromStdString(link.url)));
        ui->linksTableWidget->setItem(newRow, 2, new QTableWidgetItem(QString::fromStdString(link.folder)));
        ui->linksTableWidget->setItem(newRow, 3, new QTableWidgetItem(QString::fromStdString(link.context)));
        ui->linksTableWidget->setItem(newRow, 4, new QTableWidgetItem(QString::fromStdString(link.comment)));
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
    dialog.setFolders(m_linkManager.getFolders());
    dialog.setContexts(m_linkManager.getContexts());

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
    Q_UNUSED(arg1);
    on_searchButton_clicked();
}


void MainWindow::on_linksTableWidget_cellDoubleClicked(int row, int column)
{
    if (column == 1)
    {
        QString urlString = ui->linksTableWidget->item(row, 1)->text();
        QDesktopServices::openUrl(QUrl(urlString));
    }
}


void MainWindow::on_exportButton_clicked()
{
    ExportDialog dialog(this);
    dialog.setLinks(m_linkManager.getLinks());

    dialog.exec();
}



void MainWindow::on_manageFoldersButton_clicked()
{
    FolderManagerDialog dialog(&m_linkManager, this);
    dialog.exec();
    updateTable(m_linkManager.getLinks());
}


void MainWindow::on_manageContextsButton_clicked()
{
    ContextManagerDialog dialog(&m_linkManager, this);
    dialog.exec();
    updateTable(m_linkManager.getLinks());
}


void MainWindow::on_filterButton_clicked()
{
    FilterDialog dialog(&m_linkManager, this);

    if (m_isFilterInitialized) {
        dialog.setSelection(m_checkedFolders, m_checkedContexts);
    }

    if (dialog.exec() == QDialog::Accepted) {
        m_checkedFolders = dialog.getSelectedFolders();
        m_checkedContexts = dialog.getSelectedContexts();
        m_isFilterInitialized = true;
        std::vector<LinkData> filteredLinks = m_linkManager.filterLinks(m_checkedFolders, m_checkedContexts);
        updateTable(filteredLinks);
    }
}


void MainWindow::on_searchOnlineButton_clicked()
{
    int selectedRow = ui->linksTableWidget->currentRow();
    if (selectedRow < 0) {
        QMessageBox::information(this, "Інфо", "Оберіть посилання, яке хочете знайти.");
        return;
    }
    QString name = ui->linksTableWidget->item(selectedRow, 0)->text();
    if (name.isEmpty()) return;
    QString searchUrl = "https://www.google.com/search?q=" + QUrl::toPercentEncoding(name);
    QDesktopServices::openUrl(QUrl(searchUrl));
}


void MainWindow::on_actionSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Зберегти посилання як...", "", "JSON Files (*.json);;All Files (*)");

    if (fileName.isEmpty()) {
        return;
    }

    bool success = m_linkManager.saveToFile(fileName.toStdString());

    if (success) {
        QMessageBox::information(this, "Успіх", "Файл успішно збережено!");
    } else {
        QMessageBox::critical(this, "Помилка", "Не вдалося зберегти файл.");
    }
}


