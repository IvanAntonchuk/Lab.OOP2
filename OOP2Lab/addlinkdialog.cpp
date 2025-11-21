#include "addlinkdialog.h"
#include "ui_addlinkdialog.h"

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
    data.context = ui->contextComboBox->currentText().toStdString();

    data.comment = ui->commentTextEdit->toPlainText().toStdString();
    return data;
}

void AddLinkDialog::setLinkData(const LinkData& data)
{
    ui->nameLineEdit->setText(QString::fromStdString(data.name));
    ui->urlLineEdit->setText(QString::fromStdString(data.url));
    ui->commentTextEdit->setPlainText(QString::fromStdString(data.comment));
    ui->folderComboBox->setCurrentText(QString::fromStdString(data.folder));
    ui->contextComboBox->setCurrentText(QString::fromStdString(data.context));
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
    QString currentText = ui->contextComboBox->currentText();
    ui->contextComboBox->clear();
    ui->contextComboBox->addItem("");
    for (const auto& c : contexts) {
        ui->contextComboBox->addItem(QString::fromStdString(c));
    }
    if (!currentText.isEmpty()) {
        ui->contextComboBox->setCurrentText(currentText);
    }
}
