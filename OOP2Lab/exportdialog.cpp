#include "exportdialog.h"
#include "ui_exportdialog.h"

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
    QString result = "";
    QString format = ui->formatComboBox->currentText();

    for (const auto& link : m_dataToExport)
    {
        if (format == "Simple List")
        {
            result += QString::fromStdString(link.name) + " (" +
                      QString::fromStdString(link.url) + ")\n";
        }
        else if (format == "BibTeX")
        {
            result += "@misc{link,\n";
            result += "  title = {" + QString::fromStdString(link.name) + "},\n";
            result += "  howpublished = {\\url{" + QString::fromStdString(link.url) + "}},\n";
            result += "  note = {" + QString::fromStdString(link.comment) + "}\n";
            result += "}\n\n";
        }
    }
    ui->resultTextEdit->setText(result);
}
