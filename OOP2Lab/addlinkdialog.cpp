#include "addlinkdialog.h"
#include "ui_addlinkdialog.h"
#include "stb_image.h"

#include <QListWidgetItem>
#include <QMessageBox>
#include <QBuffer>

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

    QPixmap pix = ui->iconPreviewLabel->pixmap(Qt::ReturnByValue);

    if (!pix.isNull()) {
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        pix.save(&buffer, "PNG");
        data.iconData = bytes.toBase64().toStdString();
    }

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
        auto items = ui->contextListWidget->findItems(QString::fromStdString(ctxName), Qt::MatchExactly);
        if (!items.isEmpty()) {
            items.first()->setCheckState(Qt::Checked);
        }
    }
    if (!data.iconData.empty()) {
        QByteArray bytes = QByteArray::fromBase64(QByteArray::fromStdString(data.iconData));
        QPixmap pix;
        pix.loadFromData(bytes, "PNG");
        ui->iconPreviewLabel->setPixmap(pix);
    } else {
        ui->iconPreviewLabel->clear();
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

    ui->iconPreviewLabel->clear();
    ui->iconPreviewLabel->setToolTip("");

    std::string host;
    std::string path = "/";
    int schemeEnd = 0;

    size_t pos = urlStr.find("://");
    if (pos != std::string::npos) schemeEnd = pos + 3;

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
                ui->nameLineEdit->setText(QString::fromStdString(match[1].str()));
            }
        }

        httplib::Client googleCli("www.google.com");
        googleCli.set_connection_timeout(5, 0);
        googleCli.set_follow_location(true);

        std::string googlePath = "/s2/favicons?domain=" + host + "&sz=64";
        auto resIcon = googleCli.Get(googlePath.c_str());

        bool iconLoaded = false;

        if (resIcon && resIcon->status == 200) {
            std::string imgData = resIcon->body;
            int w, h, channels;
            unsigned char* data = stbi_load_from_memory(
                reinterpret_cast<const unsigned char*>(imgData.data()),
                imgData.size(), &w, &h, &channels, 4);

            if (data) {
                QImage qImg(data, w, h, w * 4, QImage::Format_RGBA8888);
                QPixmap pixmap = QPixmap::fromImage(qImg.copy());
                ui->iconPreviewLabel->setPixmap(pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                ui->iconPreviewLabel->setToolTip("Іконка сайту");
                stbi_image_free(data);
                iconLoaded = true;
            }
        }

        if (!iconLoaded) {
            QFont f = ui->iconPreviewLabel->font();
            f.setPointSize(16);
            ui->iconPreviewLabel->setFont(f);
            ui->iconPreviewLabel->setText("🌐");
            ui->iconPreviewLabel->setToolTip("Стандартна іконка (оригінал не знайдено)");
        }

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Помилка", e.what());
    }

    QApplication::restoreOverrideCursor();
}

