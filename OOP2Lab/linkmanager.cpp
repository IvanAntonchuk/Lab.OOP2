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
