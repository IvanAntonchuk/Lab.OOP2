#include "exportdialog.h"
#include "ui_exportdialog.h"
#include "csvexportstrategy.h"
#include "htmlexportstrategy.h"

#include <QFileDialog>
#include <QMessageBox>
#include <memory>

ExportDialog::ExportDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExportDialog)
{
    ui->setupUi(this);

    ui->formatComboBox->clear();
    ui->formatComboBox->addItem("CSV (Таблиця Excel)");
    ui->formatComboBox->addItem("HTML (Веб-сторінка)");
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
    if (m_dataToExport.empty()) {
        QMessageBox::warning(this, "Увага", "Немає посилань для експорту!");
        return;
    }

    QString formatStr = ui->formatComboBox->currentText();

    std::unique_ptr<IExportStrategy> strategy;

    QString filter;
    QString defaultExt;

    if (formatStr == "CSV (Таблиця Excel)") {
        strategy = std::make_unique<CsvExportStrategy>();
        filter = "CSV Files (*.csv)";
        defaultExt = ".csv";
    }
    else if (formatStr == "HTML (Веб-сторінка)") {
        strategy = std::make_unique<HtmlExportStrategy>();
        filter = "HTML Files (*.html)";
        defaultExt = ".html";
    }

    if (!strategy) return;

    QString filePath = QFileDialog::getSaveFileName(this, "Зберегти експорт як...", "ExportedLinks" + defaultExt, filter);

    if (filePath.isEmpty()) {
        return;
    }

    bool success = strategy->exportData(filePath, m_dataToExport);

    if (success) {
        QMessageBox::information(this, "Успіх", "Файл успішно збережено за адресою:\n" + filePath);
        ui->resultTextEdit->setText("Експорт завершено успішно!\nФормат: " + formatStr + "\nШлях: " + filePath);
    } else {
        QMessageBox::critical(this, "Помилка", "Сталася помилка під час запису у файл.");
        ui->resultTextEdit->setText("Помилка експорту.");
    }
}
