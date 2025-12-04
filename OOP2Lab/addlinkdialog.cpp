#include "addlinkdialog.h"
#include "ui_addlinkdialog.h"

#include <QListWidgetItem>
#include <QMessageBox>

#include <regex>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

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

void AddLinkDialog::on_fetchTitleButton_clicked()
{
    std::string urlStr = ui->urlLineEdit->text().toStdString();
    if (urlStr.empty()) {
        QMessageBox::warning(this, "Помилка", "Введіть URL адресу!");
        return;
    }

    std::string host;
    std::string path = "/";
    int schemeEnd = 0;

    size_t pos = urlStr.find("://");
    if (pos != std::string::npos) {
        schemeEnd = pos + 3;
    }

    size_t pathStart = urlStr.find('/', schemeEnd);
    if (pathStart != std::string::npos) {
        host = urlStr.substr(schemeEnd, pathStart - schemeEnd);
        path = urlStr.substr(pathStart);
    } else {
        host = urlStr.substr(schemeEnd);
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);

    try {
        httplib::Client cli(host);
        cli.set_connection_timeout(5, 0);
        cli.set_read_timeout(5, 0);
        cli.set_follow_location(true);
        auto res = cli.Get(path.c_str());

        if (res && res->status == 200) {
            std::string body = res->body;
            std::regex titleRegex("<title>(.*?)</title>", std::regex_constants::icase);
            std::smatch match;

            if (std::regex_search(body, match, titleRegex) && match.size() > 1) {
                std::string title = match[1].str();
                ui->nameLineEdit->setText(QString::fromStdString(title));
            } else {
                QMessageBox::information(this, "Інфо", "Тег <title> не знайдено.");
            }
        } else {
            std::string errCode = res ? std::to_string(res->status) : "Connection Error";
            if (urlStr.find("https") != std::string::npos && !res) {
                QMessageBox::warning(this, "Помилка",
                                     "Не вдалося з'єднатися. Для HTTPS потрібні OpenSSL бібліотеки, спробуйте HTTP посилання.");
            } else {
                QMessageBox::warning(this, "Помилка", QString::fromStdString("Помилка: " + errCode));
            }
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Виключення", e.what());
    }

    QApplication::restoreOverrideCursor();
}

