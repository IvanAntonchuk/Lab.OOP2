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


private:
    std::vector<LinkData> m_links;
};

#endif // LINKMANAGER_H
