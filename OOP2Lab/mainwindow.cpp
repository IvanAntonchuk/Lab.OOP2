#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "exportdialog.h"
#include "foldermanagerdialog.h"
#include "contextmanagerdialog.h"
#include "filterdialog.h"
#include "qrdialog.h"
#include "maincontroller.h"

#include "csvimportstrategy.h"
#include "jsonimportstrategy.h"
#include <memory>

#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QDragEnterEvent>
#include <QDropEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->linksTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_isFilterInitialized = false;

    m_controller = std::make_unique<MainController>(this);

    m_controller->initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    AddLinkDialog dialog(this);
    dialog.setFolders(m_controller->getFolders());
    dialog.setContexts(m_controller->getContexts());

    if (dialog.exec() == QDialog::Accepted)
    {
        LinkData newData = dialog.getLinkData();
        m_controller->addLink(newData);
    }
}

void MainWindow::updateTable(const std::vector<LinkData>& links)
{
    ui->linksTableWidget->clearContents();
    ui->linksTableWidget->setRowCount(0);
    if (ui->linksTableWidget->columnCount() < 6) {
        ui->linksTableWidget->setColumnCount(6);
        ui->linksTableWidget->setHorizontalHeaderLabels({"Назва", "URL", "Папка", "Контекст", "Пов'язане", "Коментар"});
    }

    for (const LinkData& link : links)
    {
        int newRow = ui->linksTableWidget->rowCount();
        ui->linksTableWidget->insertRow(newRow);
        QTableWidgetItem* nameItem = new QTableWidgetItem(QString::fromStdString(link.name));

        if (!link.iconData.empty()) {
            QByteArray bytes = QByteArray::fromBase64(QByteArray::fromStdString(link.iconData));
            QPixmap pix;
            pix.loadFromData(bytes, "PNG");
            nameItem->setIcon(QIcon(pix));
        }
        ui->linksTableWidget->setItem(newRow, 0, nameItem);

        ui->linksTableWidget->setItem(newRow, 1, new QTableWidgetItem(QString::fromStdString(link.url)));
        ui->linksTableWidget->setItem(newRow, 2, new QTableWidgetItem(QString::fromStdString(link.folder)));

        QString contextStr;
        for (const auto& c : link.contexts) {
            if (!contextStr.isEmpty()) contextStr += ", ";
            contextStr += QString::fromStdString(c);
        }
        ui->linksTableWidget->setItem(newRow, 3, new QTableWidgetItem(contextStr));

        ui->linksTableWidget->setItem(newRow, 4, new QTableWidgetItem(QString::fromStdString(link.relatedUrl)));
        ui->linksTableWidget->setItem(newRow, 5, new QTableWidgetItem(QString::fromStdString(link.comment)));
    }
    ui->linksTableWidget->resizeColumnsToContents();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void MainWindow::on_deleteButton_clicked()
{
    int selectedRow = ui->linksTableWidget->currentRow();
    if (selectedRow < 0) return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження видалення", "Ви справді хочете видалити це посилання?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        m_controller->deleteLink(selectedRow);
    }
}

void MainWindow::on_editButton_clicked()
{
    int selectedRow = ui->linksTableWidget->currentRow();
    if (selectedRow < 0) return;

    LinkData currentData = m_controller->getAllLinks()[selectedRow];

    AddLinkDialog dialog(this);
    dialog.setFolders(m_controller->getFolders());
    dialog.setContexts(m_controller->getContexts());
    dialog.setLinkData(currentData);

    if (dialog.exec() == QDialog::Accepted)
    {
        LinkData updatedData = dialog.getLinkData();
        m_controller->updateLink(selectedRow, updatedData);
    }
}

void MainWindow::on_searchButton_clicked()
{
    std::string query = ui->searchLineEdit->text().toStdString();
    m_controller->searchLinks(query);
}

void MainWindow::on_searchLineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    on_searchButton_clicked();
}

void MainWindow::on_linksTableWidget_cellDoubleClicked(int row, int column)
{
    if (column == 1 || column == 4)
    {
        QString urlString = ui->linksTableWidget->item(row, column)->text();
        if (!urlString.isEmpty()) {
            QDesktopServices::openUrl(QUrl(urlString));
        }
    }
}

void MainWindow::on_exportButton_clicked()
{
    ExportDialog dialog(this);
    dialog.setLinks(m_controller->getAllLinks());
    dialog.exec();
}

void MainWindow::on_manageFoldersButton_clicked()
{
    FolderManagerDialog dialog(m_controller->getLinkManager(), this);
    dialog.exec();
    updateTable(m_controller->getAllLinks());
}

void MainWindow::on_manageContextsButton_clicked()
{
    ContextManagerDialog dialog(m_controller->getLinkManager(), this);
    dialog.exec();
    updateTable(m_controller->getAllLinks());
}

void MainWindow::on_filterButton_clicked()
{
    FilterDialog dialog(m_controller->getLinkManager(), this);

    if (m_isFilterInitialized) {
        dialog.setSelection(m_checkedFolders, m_checkedContexts);
    }

    if (dialog.exec() == QDialog::Accepted) {
        m_checkedFolders = dialog.getSelectedFolders();
        m_checkedContexts = dialog.getSelectedContexts();
        m_isFilterInitialized = true;

        m_controller->filterLinks(m_checkedFolders, m_checkedContexts);
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

    if (fileName.isEmpty()) return;

    bool success = m_controller->getLinkManager()->saveToFile(fileName.toStdString());

    if (success) {
        QMessageBox::information(this, "Успіх", "Файл успішно збережено!");
    } else {
        QMessageBox::critical(this, "Помилка", "Не вдалося зберегти файл.");
    }
}

void MainWindow::on_importButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Імпортувати посилання", "", "Всі підтримувані (*.csv *.json);;CSV Files (*.csv);;JSON Files (*.json)");

    if (fileName.isEmpty()) return;

    std::unique_ptr<IImportStrategy> strategy;

    if (fileName.endsWith(".csv", Qt::CaseInsensitive)) {
        strategy = std::make_unique<CsvImportStrategy>();
    }
    else if (fileName.endsWith(".json", Qt::CaseInsensitive)) {
        strategy = std::make_unique<JsonImportStrategy>();
    }

    if (!strategy) {
        QMessageBox::warning(this, "Помилка", "Невідомий формат файлу.");
        return;
    }

    std::vector<LinkData> newLinks = strategy->importData(fileName);

    if (newLinks.empty()) {
        QMessageBox::warning(this, "Увага", "Файл порожній або сталася помилка читання.");
        return;
    }

    int count = 0;
    for (const auto& link : newLinks) {
        m_controller->getLinkManager()->addLink(link);
        count++;
    }

    updateTable(m_controller->getAllLinks());
    QMessageBox::information(this, "Успіх", QString("Успішно імпортовано %1 посилань.").arg(count));
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) return;

    QString urlStr = urls.first().toString();

    AddLinkDialog dialog(this);
    dialog.setFolders(m_controller->getFolders());
    dialog.setContexts(m_controller->getContexts());

    LinkData data;
    data.url = urlStr.toStdString();
    dialog.setLinkData(data);

    if (dialog.exec() == QDialog::Accepted)
    {
        LinkData newData = dialog.getLinkData();
        m_controller->addLink(newData);
        QMessageBox::information(this, "Успіх", "Посилання додано через Drag&Drop!");
    }
}

void MainWindow::on_qrCodeButton_clicked()
{
    int currentRow = ui->linksTableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::information(this, "Інфо", "Оберіть посилання зі списку!");
        return;
    }

    QString url = ui->linksTableWidget->item(currentRow, 1)->text();

    if (url.isEmpty()) {
        QMessageBox::warning(this, "Увага", "Посилання порожнє!");
        return;
    }

    QRDialog dlg(this);
    dlg.generateQR(url.toStdString());
    dlg.exec();
}
