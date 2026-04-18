#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "linkmanager.h"
#include <QString>
#include <vector>
#include <string>

class MainWindow;

class MainController {
public:
    MainController(MainWindow* view);
    ~MainController();

    void initialize();
    void addLink(const LinkData& data);
    void deleteLink(int index);
    void updateLink(int index, const LinkData& data);

    void searchLinks(const std::string& query);
    void filterLinks(const std::vector<std::string>& folders, const std::vector<std::string>& contexts);

    std::vector<std::string> getFolders() const;
    std::vector<std::string> getContexts() const;
    const std::vector<LinkData>& getAllLinks() const;

    LinkManager* getLinkManager();

private:
    MainWindow* m_view;
    LinkManager m_linkManager;
    QString m_saveFilePath;
};

#endif // MAINCONTROLLER_H
