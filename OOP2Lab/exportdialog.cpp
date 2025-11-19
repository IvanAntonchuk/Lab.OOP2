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
        else if (format == "DSTU 8302:2015")
        {
            result += QString::fromStdString(link.name) + " [Електронний ресурс]. – Режим доступу: " +
                      QString::fromStdString(link.url) + ".";
            if (!link.comment.empty()) {
                result += " – Прим.: " + QString::fromStdString(link.comment);
            }
            result += "\n";
        }
        else if (format == "Harvard")
        {
            result += QString::fromStdString(link.name) + ". Available at: " +
                      QString::fromStdString(link.url) + ".";

            if (!link.comment.empty()) {
                result += " (Notes: " + QString::fromStdString(link.comment) + ").";
            }
            result += "\n";
        }
    }

    ui->resultTextEdit->setText(result);
}
