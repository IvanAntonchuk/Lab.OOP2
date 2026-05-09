#include "jsonimportstrategy.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

std::vector<LinkData> JsonImportStrategy::importData(const QString& filePath) const {
    std::vector<LinkData> importedLinks;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Помилка відкриття JSON файлу для читання.";
        return importedLinks;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Помилка парсингу JSON:" << error.errorString();
        return importedLinks;
    }

    if (doc.isArray()) {
        QJsonArray arr = doc.array();
        for (int i = 0; i < arr.size(); ++i) {
            QJsonObject obj = arr[i].toObject();
            LinkData link;
            link.name = obj["name"].toString().toStdString();
            link.url = obj["url"].toString().toStdString();
            link.folder = obj["folder"].toString().toStdString();
            link.relatedUrl = obj["related_url"].toString().toStdString();
            link.comment = obj["comment"].toString().toStdString();
            link.iconData = obj["icon_data"].toString().toStdString();

            QJsonArray ctxArr = obj["contexts"].toArray();
            for (int j = 0; j < ctxArr.size(); ++j) {
                link.contexts.push_back(ctxArr[j].toString().toStdString());
            }

            importedLinks.push_back(link);
        }
    }

    return importedLinks;
}
