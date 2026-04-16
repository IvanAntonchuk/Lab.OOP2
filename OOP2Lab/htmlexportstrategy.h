#ifndef HTMLEXPORTSTRATEGY_H
#define HTMLEXPORTSTRATEGY_H

#include "iexportstrategy.h"

class HtmlExportStrategy : public IExportStrategy {
public:
    bool exportData(const QString& filePath, const std::vector<LinkData>& links) const override;
};

#endif // HTMLEXPORTSTRATEGY_H
