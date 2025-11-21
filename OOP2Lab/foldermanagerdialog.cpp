#include "foldermanagerdialog.h"
#include "ui_foldermanagerdialog.h"
#include <QTreeWidgetItem>
#include <QStringList>
#include <QMessageBox>
#include <QHash>

FolderManagerDialog::FolderManagerDialog(LinkManager* manager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FolderManagerDialog),
    m_manager(manager)
{
    ui->setupUi(this);
    ui->folderTreeWidget->setHeaderLabels({"Папки"});
    loadFoldersToTree();
}

FolderManagerDialog::~FolderManagerDialog()
{
    delete ui;
}

void FolderManagerDialog::loadFoldersToTree()
{
    ui->folderTreeWidget->clear();
    QHash<QString, QTreeWidgetItem*> items;

    const std::vector<std::string>& folders = m_manager->getFolders();

    for (const std::string& f : folders)
    {
        QString path = QString::fromStdString(f);
        QStringList parts = path.split('/', Qt::SkipEmptyParts);
        QTreeWidgetItem* currentParent = nullptr;

        for(int i = 0; i < parts.size(); ++i) {
            QString currentPathSegment = parts.mid(0, i + 1).join('/');
            if (!items.contains(currentPathSegment)) {
                QTreeWidgetItem* newItem;
                if (currentParent) {
                    newItem = new QTreeWidgetItem(currentParent);
                } else {
                    newItem = new QTreeWidgetItem(ui->folderTreeWidget);
                }
                newItem->setText(0, parts.at(i));
                items[currentPathSegment] = newItem;
                currentParent = newItem;
            } else {
                currentParent = items[currentPathSegment];
            }
        }
    }
    ui->folderTreeWidget->expandAll();
}

void FolderManagerDialog::on_createFolderButton_clicked()
{
    QString newName = ui->newFolderLineEdit->text().trimmed();

    if (newName.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Назва папки не може бути порожньою.");
        return;
    }

    QString fullPath = newName;

    QTreeWidgetItem* selectedItem = ui->folderTreeWidget->currentItem();

    if (selectedItem) {
        QString parentPath = selectedItem->text(0);
        QTreeWidgetItem* parent = selectedItem->parent();
        while (parent) {
            parentPath = parent->text(0) + "/" + parentPath;
            parent = parent->parent();
        }
        fullPath = parentPath + "/" + newName;
    }

    std::string newFolderStd = fullPath.toStdString();

    if (m_manager->hasFolder(newFolderStd)) {
        QMessageBox::warning(this, "Помилка", "Така папка вже існує!");
        return;
    }

    m_manager->addFolder(newFolderStd);

    loadFoldersToTree();

    ui->newFolderLineEdit->clear();
}

void FolderManagerDialog::on_deleteFolderButton_clicked()
{
    QTreeWidgetItem* selectedItem = ui->folderTreeWidget->currentItem();

    if (!selectedItem) return;

    QString fullPath = selectedItem->text(0);
    QTreeWidgetItem* parent = selectedItem->parent();
    while (parent) {
        fullPath = parent->text(0) + "/" + fullPath;
        parent = parent->parent();
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження", "Видалити папку '" + fullPath + "'?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        m_manager->clearLinksFolder(fullPath.toStdString());
        m_manager->removeFolder(fullPath.toStdString());
        loadFoldersToTree();
    }
}

void FolderManagerDialog::on_deselectButton_clicked()
{
    ui->folderTreeWidget->clearSelection();
}
