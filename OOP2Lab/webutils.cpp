#include "webutils.h"
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QDebug>

WebUtils::WebUtils(QObject *parent) : QObject(parent)
{
    netManager = new QNetworkAccessManager(this);
    connect(netManager, &QNetworkAccessManager::finished, this, &WebUtils::onReplyFinished);
}

void WebUtils::fetchTitleAsync(const QString& urlString)
{
    QUrl url(urlString);
    QNetworkRequest request(url);
    netManager->get(request);
}

void WebUtils::onReplyFinished(QNetworkReply *reply)
{
    QString url = reply->request().url().toString();
    QString title = url;

    if (reply->error() == QNetworkReply::NoError) {
        QString html = QString::fromUtf8(reply->readAll());
        QRegularExpression re("<title>(.*?)</title>", QRegularExpression::CaseInsensitiveOption);
        QRegularExpressionMatch match = re.match(html);
        if (match.hasMatch()) {
            title = match.captured(1).trimmed();
        }
    } else {
        qDebug() << "Помилка мережі:" << reply->errorString();
    }

    reply->deleteLater();
    emit titleReady(url, title);
}
