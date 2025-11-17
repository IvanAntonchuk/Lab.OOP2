#include "linkmanager.h"

LinkManager::LinkManager() {
}

void LinkManager::addLink(const LinkData& newLink) {
    m_links.push_back(newLink);
}

const std::vector<LinkData>& LinkManager::getLinks() const {
    return m_links;
}

void LinkManager::loadLinks(const std::vector<LinkData>& links)
{
    m_links = links;
}

void LinkManager::deleteLink(int index)
{
    if (index >= 0 && index < m_links.size())
    {
        m_links.erase(m_links.begin() + index);
    }
}

void LinkManager::updateLink(int index, const LinkData& updatedData)
{
    if (index >= 0 && index < m_links.size())
    {
        m_links[index] = updatedData;
    }
}

// ↓↓↓ КОПІЮЙТЕ ЦЕ В КІНЕЦЬ ФАЙЛУ ↓↓↓
std::vector<LinkData> LinkManager::searchLinks(const std::string& query) const
{
    std::vector<LinkData> results;

    if (query.empty()) {
        return m_links;
    }
    for (const auto& link : m_links)
    {
        if (link.name.find(query) != std::string::npos ||
            link.url.find(query) != std::string::npos ||
            link.comment.find(query) != std::string::npos)
        {
            results.push_back(link);
        }
    }

    return results;
}
