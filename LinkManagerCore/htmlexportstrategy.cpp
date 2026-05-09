#include "htmlexportstrategy.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

bool HtmlExportStrategy::exportData(const QString& filePath, const std::vector<LinkData>& links) const {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Помилка: не вдалося HTML файл:" << filePath;
        return false;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    out << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n";
    out << "<title>Експортовані посилання</title>\n</head>\n<body>\n";
    out << "<h1>Мої посилання</h1>\n<ul>\n";

    for (const auto& link : links) {
        QString name = QString::fromStdString(link.name);
        QString url = QString::fromStdString(link.url);
        out << "<li><a href=\"" << url << "\">" << name << "</a></li>\n";
    }

    out << "</ul>\n</body>\n</html>\n";
    file.close();
    return true;
}
