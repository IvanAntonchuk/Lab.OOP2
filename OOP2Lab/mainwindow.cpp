#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "exportdialog.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
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

    loadLinksFromFile();

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
    saveLinksToFile();
    event->accept();
}

void MainWindow::saveLinksToFile()
{
    QJsonArray linksArray;

    const auto& links = m_linkManager.getLinks();

    for (const auto& link : links)
    {
        QJsonObject linkObject;
        linkObject["name"]    = QString::fromStdString(link.name);
        linkObject["url"]     = QString::fromStdString(link.url);
        linkObject["context"] = QString::fromStdString(link.context);
        linkObject["comment"] = QString::fromStdString(link.comment);

        linksArray.append(linkObject);
    }
    QJsonDocument doc(linksArray);
    QFile file(m_saveFilePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    file.write(doc.toJson());
    file.close();
}


void MainWindow::loadLinksFromFile()
{
    QFile file(m_saveFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug("No save file found.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (!doc.isArray()) {
        qWarning("Save file is corrupted.");
        return;
    }

    QJsonArray linksArray = doc.array();
    std::vector<LinkData> loadedLinks;

    for (const QJsonValue& value : linksArray)
    {
        if (!value.isObject()) {
            continue;
        }

        QJsonObject obj = value.toObject();
        LinkData link;

        link.name    = obj["name"].toString().toStdString();
        link.url     = obj["url"].toString().toStdString();
        link.context = obj["context"].toString().toStdString();
        link.comment = obj["comment"].toString().toStdString();

        loadedLinks.push_back(link);
    }

    m_linkManager.loadLinks(loadedLinks);
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


