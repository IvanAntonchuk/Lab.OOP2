#include "csvimportstrategy.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>

std::vector<LinkData> CsvImportStrategy::importData(const QString& filePath) const {
    std::vector<LinkData> importedLinks;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Помилка відкриття CSV файлу для читання.";
        return importedLinks;
    }

    QTextStream in(&file);
    if (!in.atEnd()) {
        in.readLine();
    }

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("\",\"");

        if (parts.size() >= 5) {
            LinkData link;
            link.name = parts[0].remove(0, 1).toStdString();
            link.url = parts[1].toStdString();
            link.folder = parts[2].toStdString();
            link.relatedUrl = parts[3].toStdString();
            link.comment = parts[4].remove(parts[4].length() - 1, 1).toStdString();

            importedLinks.push_back(link);
        }
    }

    file.close();
    return importedLinks;
}
