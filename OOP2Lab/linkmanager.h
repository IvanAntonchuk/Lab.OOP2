#ifndef LINKMANAGER_H
#define LINKMANAGER_H

#include <string>
#include <vector>


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
    void loadLinks(const std::vector<LinkData>& links);
    void deleteLink(int index);
    void updateLink(int index, const LinkData& updatedData);
    std::vector<LinkData> searchLinks(const std::string& query) const;

private:
    std::vector<LinkData> m_links;
};

#endif // LINKMANAGER_H
