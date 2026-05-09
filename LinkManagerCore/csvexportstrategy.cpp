#include "csvexportstrategy.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

bool CsvExportStrategy::exportData(const QString& filePath, const std::vector<LinkData>& links) const {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Помилка: не вдалося створити CSV файл:" << filePath;
        return false;
    }

    QTextStream out(&file);
    out.setGenerateByteOrderMark(true);
    out << "Name,URL,Folder,Related URL,Comment\n";

    for (const auto& link : links) {
        QString name = QString::fromStdString(link.name).replace("\"", "\"\"");
        QString url = QString::fromStdString(link.url).replace("\"", "\"\"");
        QString folder = QString::fromStdString(link.folder).replace("\"", "\"\"");
        QString related = QString::fromStdString(link.relatedUrl).replace("\"", "\"\"");
        QString comment = QString::fromStdString(link.comment).replace("\"", "\"\"");

        out << "\"" << name << "\",\""
            << url << "\",\""
            << folder << "\",\""
            << related << "\",\""
            << comment << "\"\n";
    }

    file.close();
    return true;
}
