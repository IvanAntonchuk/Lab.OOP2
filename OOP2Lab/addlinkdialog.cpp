#include "addlinkdialog.h"
#include "ui_addlinkdialog.h"

#include <QListWidgetItem>

AddLinkDialog::AddLinkDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddLinkDialog)
{
    ui->setupUi(this);
}

AddLinkDialog::~AddLinkDialog()
{
    delete ui;
}

LinkData AddLinkDialog::getLinkData() const
{
    LinkData data;
    data.name    = ui->nameLineEdit->text().toStdString();
    data.url     = ui->urlLineEdit->text().toStdString();
    data.folder  = ui->folderComboBox->currentText().toStdString();

    for(int i = 0; i < ui->contextListWidget->count(); ++i) {
        QListWidgetItem* item = ui->contextListWidget->item(i);
        if (item->checkState() == Qt::Checked) {
            data.contexts.push_back(item->text().toStdString());
        }
    }

    data.relatedUrl = ui->relatedUrlLineEdit->text().toStdString();
    data.comment = ui->commentTextEdit->toPlainText().toStdString();
    return data;
}

void AddLinkDialog::setLinkData(const LinkData& data)
{
    ui->nameLineEdit->setText(QString::fromStdString(data.name));
    ui->urlLineEdit->setText(QString::fromStdString(data.url));
    ui->folderComboBox->setCurrentText(QString::fromStdString(data.folder));
    ui->relatedUrlLineEdit->setText(QString::fromStdString(data.relatedUrl));
    ui->commentTextEdit->setPlainText(QString::fromStdString(data.comment));

    for(int i = 0; i < ui->contextListWidget->count(); ++i) {
        ui->contextListWidget->item(i)->setCheckState(Qt::Unchecked);
    }

    for (const auto& ctxName : data.contexts) {
        QList<QListWidgetItem*> items = ui->contextListWidget->findItems(QString::fromStdString(ctxName), Qt::MatchExactly);
        if (!items.isEmpty()) {
            items.first()->setCheckState(Qt::Checked);
        }
    }
}

void AddLinkDialog::setFolders(const std::vector<std::string>& folders)
{
    QString currentText = ui->folderComboBox->currentText();
    ui->folderComboBox->clear();
    ui->folderComboBox->addItem("");

    for (const auto& f : folders) {
        ui->folderComboBox->addItem(QString::fromStdString(f));
    }
    ui->folderComboBox->setCurrentText(currentText);
}

void AddLinkDialog::setContexts(const std::vector<std::string>& contexts)
{
    ui->contextListWidget->clear();

    for (const auto& c : contexts) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(c), ui->contextListWidget);

        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);

        item->setCheckState(Qt::Unchecked);
    }
}
