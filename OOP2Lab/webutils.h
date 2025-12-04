#ifndef WEBUTILS_H
#define WEBUTILS_H

#include <string>
#include <QString>

class WebUtils
{
public:
    static std::string extractTitleFromHtml(const std::string& htmlBody);
};

#endif // WEBUTILS_H
