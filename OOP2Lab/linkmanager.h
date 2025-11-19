#ifndef LINKMANAGER_H
#define LINKMANAGER_H

#include <string>
#include <vector>
#include <algorithm> // Для std::find

struct LinkData {
    std::string name;
    std::string url;
    std::string context;
    std::string comment;
};

class LinkManager {
public:
    LinkManager();

    void addLink(const LinkData& newLink);
    const std::vector<LinkData>& getLinks() const;
    void deleteLink(int index);
    void updateLink(int index, const LinkData& updatedData);
    std::vector<LinkData> searchLinks(const std::string& query) const;

    void addContext(const std::string& contextName);
    const std::vector<std::string>& getContexts() const;
    void removeContext(const std::string& contextName);
    bool hasContext(const std::string& contextName) const;
    bool saveToFile(const std::string& filePath) const;
    bool loadFromFile(const std::string& filePath);

private:
    std::vector<LinkData> m_links;
    std::vector<std::string> m_contexts;
};

#endif // LINKMANAGER_H
