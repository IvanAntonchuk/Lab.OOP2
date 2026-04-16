#ifndef CSVEXPORTSTRATEGY_H
#define CSVEXPORTSTRATEGY_H

#include "iexportstrategy.h"

class CsvExportStrategy : public IExportStrategy {
public:
    bool exportData(const QString& filePath, const std::vector<LinkData>& links) const override;
};

#endif // CSVEXPORTSTRATEGY_H
