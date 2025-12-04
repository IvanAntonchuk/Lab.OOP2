#include "exportdialog.h"
#include "ui_exportdialog.h"
#include "linkserializer.h"

ExportDialog::ExportDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExportDialog)
{
    ui->setupUi(this);
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

void ExportDialog::setLinks(const std::vector<LinkData> &links)
{
    m_dataToExport = links;
}

void ExportDialog::on_closeButton_clicked()
{
    this->close();
}

void ExportDialog::on_generateButton_clicked()
{
    QString formatStr = ui->formatComboBox->currentText();
    LinkSerializer::ExportFormat format = LinkSerializer::SimpleList;

    if (formatStr == "BibTeX") format = LinkSerializer::BibTeX;
    else if (formatStr == "DSTU 8302:2015") format = LinkSerializer::DSTU8302;
    else if (formatStr == "Harvard") format = LinkSerializer::Harvard;

    QString result = LinkSerializer::exportLinks(m_dataToExport, format);

    ui->resultTextEdit->setText(result);
}
