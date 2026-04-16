#ifndef IIMPORTSTRATEGY_H
#define IIMPORTSTRATEGY_H

#include <QString>
#include <vector>
#include "linkmanager.h"

class IImportStrategy {
public:
    virtual ~IImportStrategy() = default;
    virtual std::vector<LinkData> importData(const QString& filePath) const = 0;
};

#endif // IIMPORTSTRATEGY_H
