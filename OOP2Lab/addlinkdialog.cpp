#include "addlinkdialog.h"
#include "ui_addlinkdialog.h"
#include "stb_image.h"
#include "webutils.h"

#include <QListWidgetItem>
#include <QMessageBox>
#include <QBuffer>
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

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
    QString urlStr = ui->urlLineEdit->text();
    if (urlStr.isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Введіть URL адресу!");
        return;
    }

    QFont f = ui->iconPreviewLabel->font();
    f.setPointSize(16);
    ui->iconPreviewLabel->setFont(f);
    ui->iconPreviewLabel->setText("🌐");
    ui->iconPreviewLabel->setToolTip("Завантаження іконки...");

    ui->nameLineEdit->setText("Завантаження...");

    WebUtils *webUtils = new WebUtils(this);
    connect(webUtils, &WebUtils::titleReady, this, [this, webUtils](const QString &url, const QString &title) {
        ui->nameLineEdit->setText(title);
        webUtils->deleteLater();
    });
    webUtils->fetchTitleAsync(urlStr);

    QUrl parsedUrl(urlStr);
    QString host = parsedUrl.host();
    if (host.isEmpty()) host = urlStr;

    QString iconUrl = QString("http://www.google.com/s2/favicons?domain=%1&sz=64").arg(host);

    QNetworkAccessManager *iconManager = new QNetworkAccessManager(this);
    QNetworkRequest iconRequest((QUrl(iconUrl)));

    iconRequest.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);

    QNetworkReply *iconReply = iconManager->get(iconRequest);

    connect(iconReply, &QNetworkReply::finished, this, [this, iconReply, iconManager]() {
        if (iconReply->error() == QNetworkReply::NoError) {
            QByteArray imgData = iconReply->readAll();

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
            } else {
                ui->iconPreviewLabel->setToolTip("Стандартна іконка (оригінал не знайдено)");
            }
        } else {
            ui->iconPreviewLabel->setToolTip("Стандартна іконка (помилка мережі)");
        }

        iconReply->deleteLater();
        iconManager->deleteLater();
    });
}
