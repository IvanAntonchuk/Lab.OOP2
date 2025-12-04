#include "webutils.h"
#include <regex>

std::string WebUtils::extractTitleFromHtml(const std::string& htmlBody)
{
    std::regex titleRegex("<title>(.*?)</title>", std::regex_constants::icase);
    std::smatch match;

    if (std::regex_search(htmlBody, match, titleRegex) && match.size() > 1) {
        return match[1].str();
    }

    return "";
}
