#include "linkserializer.h"
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QString LinkSerializer::exportLinks(const std::vector<LinkData>& links, ExportFormat format)
{
    QString result = "";

    for (const auto& link : links)
    {
        if (format == SimpleList)
        {
            result += QString::fromStdString(link.name) + " (" +
                      QString::fromStdString(link.url) + ")\n";
        }
        else if (format == BibTeX)
        {
            result += "@misc{link,\n";
            result += "  title = {" + QString::fromStdString(link.name) + "},\n";
            result += "  howpublished = {\\url{" + QString::fromStdString(link.url) + "}},\n";
            result += "  note = {" + QString::fromStdString(link.comment) + "}\n";
            result += "}\n\n";
        }
        else if (format == DSTU8302)
        {
            result += QString::fromStdString(link.name) + " [Електронний ресурс]. – Режим доступу: " +
                      QString::fromStdString(link.url) + ".";
            if (!link.comment.empty()) {
                result += " – Прим.: " + QString::fromStdString(link.comment);
            }
            result += "\n";
        }
        else if (format == Harvard)
        {
            result += QString::fromStdString(link.name) + ". Available at: " +
                      QString::fromStdString(link.url) + ".";

            if (!link.comment.empty()) {
                result += " (Notes: " + QString::fromStdString(link.comment) + ").";
            }
            result += "\n";
        }
    }
    return result;
}

std::vector<LinkData> LinkSerializer::importFromCSV(const QString& csvContent)
{
    std::vector<LinkData> result;
    QStringList lines = csvContent.split('\n');

    for (const QString& line : lines) {
        if (line.trimmed().isEmpty()) continue;

        QStringList parts = line.split(';');
        if (parts.size() >= 2) {
            LinkData link;
            link.name = parts[0].trimmed().toStdString();
            link.url = parts[1].trimmed().toStdString();

            if (parts.size() > 2) link.folder = parts[2].trimmed().toStdString();
            if (parts.size() > 3) link.contexts.push_back(parts[3].trimmed().toStdString());
            if (parts.size() > 4) link.comment = parts[4].trimmed().toStdString();

            result.push_back(link);
        }
    }
    return result;
}

std::vector<LinkData> LinkSerializer::importFromJSON(const QByteArray& jsonData)
{
    std::vector<LinkData> result;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);

    if (!doc.isNull() && doc.isObject()) {
        QJsonObject root = doc.object();
        if (root.contains("links") && root["links"].isArray()) {
            QJsonArray linksArray = root["links"].toArray();
            for (const auto& val : linksArray) {
                QJsonObject obj = val.toObject();
                LinkData link;
                link.name = obj["name"].toString().toStdString();
                link.url = obj["url"].toString().toStdString();

                if (obj.contains("folder")) link.folder = obj["folder"].toString().toStdString();

                if (obj.contains("contexts") && obj["contexts"].isArray()) {
                    for (const auto& c : obj["contexts"].toArray()) {
                        link.contexts.push_back(c.toString().toStdString());
                    }
                } else if (obj.contains("context")) {
                    link.contexts.push_back(obj["context"].toString().toStdString());
                } else if (obj.contains("type")) {
                    link.contexts.push_back(obj["type"].toString().toStdString());
                }

                link.comment = obj["comment"].toString().toStdString();
                result.push_back(link);
            }
        }
    }
    return result;
}
