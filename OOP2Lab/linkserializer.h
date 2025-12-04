#ifndef LINKSERIALIZER_H
#define LINKSERIALIZER_H

#include <QString>
#include <vector>
#include "linkmanager.h"

class LinkSerializer
{
public:
    enum ExportFormat {
        SimpleList,
        BibTeX,
        DSTU8302,
        Harvard
    };

    static QString exportLinks(const std::vector<LinkData>& links, ExportFormat format);
    static std::vector<LinkData> importFromCSV(const QString& csvContent);
    static std::vector<LinkData> importFromJSON(const QByteArray& jsonData);
};

#endif // LINKSERIALIZER_H
