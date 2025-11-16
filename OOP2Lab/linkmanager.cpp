#include "linkmanager.h"

LinkManager::LinkManager() {
}

void LinkManager::addLink(const LinkData& newLink) {
    m_links.push_back(newLink);
}

const std::vector<LinkData>& LinkManager::getLinks() const {
    return m_links;
}
