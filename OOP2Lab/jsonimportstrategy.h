#ifndef JSONIMPORTSTRATEGY_H
#define JSONIMPORTSTRATEGY_H

#include "iimportstrategy.h"

class JsonImportStrategy : public IImportStrategy {
public:
    std::vector<LinkData> importData(const QString& filePath) const override;
};

#endif // JSONIMPORTSTRATEGY_H
