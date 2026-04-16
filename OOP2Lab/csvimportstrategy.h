#ifndef CSVIMPORTSTRATEGY_H
#define CSVIMPORTSTRATEGY_H

#include "iimportstrategy.h"

class CsvImportStrategy : public IImportStrategy {
public:
    std::vector<LinkData> importData(const QString& filePath) const override;
};

#endif // CSVIMPORTSTRATEGY_H
