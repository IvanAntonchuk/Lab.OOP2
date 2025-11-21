#include "filterdialog.h"
#include "ui_filterdialog.h"
#include <QTreeWidgetItem>

FilterDialog::FilterDialog(LinkManager* manager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog),
    m_manager(manager)
{
    ui->setupUi(this);

    ui->folderTreeWidget->setHeaderLabel("Папки");

    loadData();
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

void FilterDialog::loadData()
{
    ui->folderTreeWidget->clear();
    QTreeWidgetItem* emptyFolder = new QTreeWidgetItem(ui->folderTreeWidget);
    emptyFolder->setText(0, "[Без папки]");
    emptyFolder->setData(0, Qt::UserRole, "");
    emptyFolder->setCheckState(0, Qt::Checked);

    const std::vector<std::string>& folders = m_manager->getFolders();

    for (const auto& f : folders) {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->folderTreeWidget);
        item->setText(0, QString::fromStdString(f));
        item->setCheckState(0, Qt::Checked);
    }

    ui->contextListWidget->clear();
    QListWidgetItem* emptyContext = new QListWidgetItem("[Без контексту]", ui->contextListWidget);
    emptyContext->setData(Qt::UserRole, "");
    emptyContext->setCheckState(Qt::Checked);

    const std::vector<std::string>& contexts = m_manager->getContexts();
    for (const auto& c : contexts) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(c), ui->contextListWidget);
        item->setCheckState(Qt::Checked);
    }
}

std::vector<std::string> FilterDialog::getSelectedFolders() const
{
    std::vector<std::string> selected;
    QTreeWidgetItemIterator it(ui->folderTreeWidget);
    while (*it) {
        if ((*it)->checkState(0) == Qt::Checked) {
            if ((*it)->text(0) == "[Без папки]")
                selected.push_back("");
            else
                selected.push_back((*it)->text(0).toStdString());
        }
        ++it;
    }
    return selected;
}

std::vector<std::string> FilterDialog::getSelectedContexts() const
{
    std::vector<std::string> selected;
    for (int i = 0; i < ui->contextListWidget->count(); ++i) {
        QListWidgetItem* item = ui->contextListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            if (item->text() == "[Без контексту]")
                selected.push_back("");
            else
                selected.push_back(item->text().toStdString());
        }
    }
    return selected;
}

void FilterDialog::setSelection(const std::vector<std::string>& folders, const std::vector<std::string>& contexts)
{
    QTreeWidgetItemIterator it(ui->folderTreeWidget);
    while (*it) {
        std::string value = (*it)->text(0).toStdString();
        if ((*it)->text(0) == "[Без папки]") value = "";

        bool found = false;
        for (const auto& f : folders) {
            if (f == value) { found = true; break; }
        }
        (*it)->setCheckState(0, found ? Qt::Checked : Qt::Unchecked);
        ++it;
    }

    for(int i = 0; i < ui->contextListWidget->count(); ++i) {
        QListWidgetItem* item = ui->contextListWidget->item(i);
        std::string value = item->text().toStdString();
        if (item->text() == "[Без контексту]") value = "";

        bool found = false;
        for (const auto& c : contexts) {
            if (c == value) { found = true; break; }
        }
        item->setCheckState(found ? Qt::Checked : Qt::Unchecked);
    }
}
