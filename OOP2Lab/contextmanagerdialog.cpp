#include "contextmanagerdialog.h"
#include "ui_contextmanagerdialog.h"
#include <QTreeWidgetItem>
#include <QStringList>
#include <QMessageBox>
#include <QHash>
#include <QDebug>

ContextManagerDialog::ContextManagerDialog(LinkManager* manager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContextManagerDialog),
    m_manager(manager)
{
    ui->setupUi(this);

    ui->contextTreeWidget->setHeaderLabels({"Контекст"});
    loadContextsToTree();
}

ContextManagerDialog::~ContextManagerDialog()
{
    delete ui;
}


void ContextManagerDialog::loadContextsToTree()
{
    ui->contextTreeWidget->clear();
    QHash<QString, QTreeWidgetItem*> items;
    const std::vector<std::string>& contexts = m_manager->getContexts();

    for (const std::string& ctx : contexts)
    {
        QString path = QString::fromStdString(ctx);
        QStringList parts = path.split('/', Qt::SkipEmptyParts);

        QTreeWidgetItem* currentParent = nullptr;

        for(int i = 0; i < parts.size(); ++i) {
            QString currentPathSegment = parts.mid(0, i + 1).join('/');

            if (!items.contains(currentPathSegment)) {

                QTreeWidgetItem* newItem;
                if (currentParent) {
                    newItem = new QTreeWidgetItem(currentParent);
                } else {
                    newItem = new QTreeWidgetItem(ui->contextTreeWidget);
                }

                newItem->setText(0, parts.at(i));
                items[currentPathSegment] = newItem;
                currentParent = newItem;
            } else {
                currentParent = items[currentPathSegment];
            }
        }
    }

    ui->contextTreeWidget->expandAll();
}

void ContextManagerDialog::on_createContextButton_clicked()
{
    QString newName = ui->newContextLineEdit->text().trimmed();

    if (newName.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Назва папки не може бути порожньою.");
        return;
    }

    QString fullPath = newName;
    QTreeWidgetItem* selectedItem = ui->contextTreeWidget->currentItem();

    if (selectedItem) {
        QString parentPath = selectedItem->text(0);
        QTreeWidgetItem* parent = selectedItem->parent();
        while (parent) {
            parentPath = parent->text(0) + "/" + parentPath;
            parent = parent->parent();
        }
        fullPath = parentPath + "/" + newName;
    }

    std::string newContextStd = fullPath.toStdString();
    if (m_manager->hasContext(newContextStd)) {
        QMessageBox::warning(this, "Помилка", "Така папка вже існує!");
        return;
    }
    m_manager->addContext(newContextStd);
    loadContextsToTree();

    ui->newContextLineEdit->clear();
}

void ContextManagerDialog::on_deleteContextButton_clicked()
{
    QTreeWidgetItem* selectedItem = ui->contextTreeWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::information(this, "Помилка", "Оберіть папку для видалення.");
        return;
    }
    QString fullPath = selectedItem->text(0);
    QTreeWidgetItem* parent = selectedItem->parent();
    while (parent) {
        fullPath = parent->text(0) + "/" + fullPath;
        parent = parent->parent();
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Підтвердження", "Ви впевнені, що хочете видалити папку '" + fullPath + "'? Посилання, прив'язані до неї, залишаться.", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        m_manager->clearLinksContext(fullPath.toStdString());
        m_manager->removeContext(fullPath.toStdString());
        loadContextsToTree();
    }
}

void ContextManagerDialog::on_deselectButton_clicked()
{
    ui->contextTreeWidget->clearSelection();
}

