#ifndef IEXPORTSTRATEGY_H
#define IEXPORTSTRATEGY_H

#include <QString>
#include <vector>
#include "linkmanager.h"

class IExportStrategy {
public:
    virtual ~IExportStrategy() = default;
    virtual bool exportData(const QString& filePath, const std::vector<LinkData>& links) const = 0;
};

#endif // IEXPORTSTRATEGY_H
