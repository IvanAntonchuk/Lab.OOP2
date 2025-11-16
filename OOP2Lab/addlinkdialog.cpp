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
    data.context = ui->contextComboBox->currentText().toStdString();
    data.comment = ui->commentTextEdit->toPlainText().toStdString();

    return data;
}

void AddLinkDialog::setLinkData(const LinkData& data)
{
    ui->nameLineEdit->setText(QString::fromStdString(data.name));
    ui->urlLineEdit->setText(QString::fromStdString(data.url));
    ui->commentTextEdit->setPlainText(QString::fromStdString(data.comment));
    ui->contextComboBox->setCurrentText(QString::fromStdString(data.context));
}
