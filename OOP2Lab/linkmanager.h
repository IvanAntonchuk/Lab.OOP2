#ifndef LINKMANAGER_H
#define LINKMANAGER_H

#include <string>
#include <vector>
#include <algorithm>

struct LinkData {
    std::string name;
    std::string url;
    std::string folder;
    std::vector<std::string> contexts;
    std::string relatedUrl;
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

    void addFolder(const std::string& folderName);
    const std::vector<std::string>& getFolders() const;
    void removeFolder(const std::string& folderName);
    bool hasFolder(const std::string& folderName) const;
    void clearLinksFolder(const std::string& folderName);

    void addContext(const std::string& contextName);
    const std::vector<std::string>& getContexts() const;
    void removeContext(const std::string& contextName);
    bool hasContext(const std::string& contextName) const;
    bool saveToFile(const std::string& filePath) const;
    bool loadFromFile(const std::string& filePath);

    std::vector<LinkData> filterLinks(const std::vector<std::string>& allowedFolders, const std::vector<std::string>& allowedContexts) const;

private:
    std::vector<LinkData> m_links;
    std::vector<std::string> m_folders;
    std::vector<std::string> m_contexts;
};

#endif // LINKMANAGER_H
