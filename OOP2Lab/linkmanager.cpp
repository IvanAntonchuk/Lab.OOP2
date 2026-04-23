#include "linkmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <algorithm>

LinkManager::LinkManager() {
    loadFromFile();

    if (m_contexts.empty()) {
        m_contexts.push_back("Книга");
        m_contexts.push_back("Стаття");
        m_contexts.push_back("Відео");
        m_contexts.push_back("Вебсайт");
        saveToFile();
    }
}

void LinkManager::addLink(const LinkData& newLink) {
    m_links.push_back(newLink);
    if (!newLink.folder.empty()) addFolder(newLink.folder);
    for (const auto& ctx : newLink.contexts) {
        if (!ctx.empty()) addContext(ctx);
    }
    saveToFile();
}

const std::vector<LinkData>& LinkManager::getLinks() const { return m_links; }

void LinkManager::deleteLink(int index) {
    if (index >= 0 && index < (int)m_links.size()) {
        m_links.erase(m_links.begin() + index);
        saveToFile();
    }
}

void LinkManager::updateLink(int index, const LinkData& updatedData) {
    if (index >= 0 && index < (int)m_links.size()) {
        m_links[index] = updatedData;
        if (!updatedData.folder.empty()) addFolder(updatedData.folder);
        for (const auto& ctx : updatedData.contexts) {
            if (!ctx.empty()) addContext(ctx);
        }
        saveToFile();
    }
}

std::vector<LinkData> LinkManager::searchLinks(const std::string& query) const {
    std::vector<LinkData> results;
    if (query.empty()) return m_links;
    for (const auto& link : m_links) {
        bool contextFound = false;
        for (const auto& ctx : link.contexts) {
            if (ctx.find(query) != std::string::npos) {
                contextFound = true;
                break;
            }
        }
        if (link.name.find(query) != std::string::npos ||
            link.url.find(query) != std::string::npos ||
            link.comment.find(query) != std::string::npos ||
            link.folder.find(query) != std::string::npos ||
            contextFound) {
            results.push_back(link);
        }
    }
    return results;
}

void LinkManager::addFolder(const std::string& folderName) {
    if (!hasFolder(folderName)) {
        m_folders.push_back(folderName);
        saveToFile();
    }
}

const std::vector<std::string>& LinkManager::getFolders() const { return m_folders; }

void LinkManager::removeFolder(const std::string& folderName) {
    auto it = std::remove(m_folders.begin(), m_folders.end(), folderName);
    if (it != m_folders.end()) {
        m_folders.erase(it, m_folders.end());
        saveToFile();
    }
}

bool LinkManager::hasFolder(const std::string& folderName) const {
    for (const auto& f : m_folders) if (f == folderName) return true;
    return false;
}

void LinkManager::clearLinksFolder(const std::string& folderName) {
    for (auto& link : m_links) {
        if (link.folder == folderName) link.folder = "";
    }
    saveToFile();
}

void LinkManager::addContext(const std::string& contextName) {
    if (!hasContext(contextName)) {
        m_contexts.push_back(contextName);
        saveToFile();
    }
}

const std::vector<std::string>& LinkManager::getContexts() const { return m_contexts; }

void LinkManager::removeContext(const std::string& contextName) {
    auto it = std::remove(m_contexts.begin(), m_contexts.end(), contextName);
    if (it != m_contexts.end()) {
        m_contexts.erase(it, m_contexts.end());
        saveToFile();
    }
}

bool LinkManager::hasContext(const std::string& contextName) const {
    for (const auto& c : m_contexts) if (c == contextName) return true;
    return false;
}

std::vector<LinkData> LinkManager::filterLinks(const std::vector<std::string>& allowedFolders, const std::vector<std::string>& allowedContexts) const {
    std::vector<LinkData> results;

    for (const auto& link : m_links) {
        bool folderOk = allowedFolders.empty();

        if (!folderOk) {
            for (const auto& f : allowedFolders) {
                if (link.folder == f) { folderOk = true; break; }
            }
        }
        bool contextOk = allowedContexts.empty();

        if (!contextOk) {
            for (const auto& linkCtx : link.contexts) {
                for (const auto& allowed : allowedContexts) {
                    if (linkCtx == allowed) { contextOk = true; break; }
                }
                if (contextOk) break;
            }
        }
        if (folderOk && contextOk) {
            results.push_back(link);
        }
    }
    return results;
}

bool LinkManager::saveToFile(const std::string& /*filePath*/) {
    QSqlQuery q;
    q.exec("DELETE FROM link_contexts");
    q.exec("DELETE FROM links");
    q.exec("DELETE FROM folders");
    q.exec("DELETE FROM contexts");

    q.prepare("INSERT INTO folders (name) VALUES (:name)");
    for (const auto& f : m_folders) {
        q.bindValue(":name", QString::fromStdString(f));
        q.exec();
    }

    q.prepare("INSERT INTO contexts (name) VALUES (:name)");
    for (const auto& c : m_contexts) {
        q.bindValue(":name", QString::fromStdString(c));
        q.exec();
    }

    for (const auto& link : m_links) {
        q.prepare("INSERT INTO links (name, url, folder, related_url, comment, icon_data) "
                  "VALUES (:name, :url, :folder, :related_url, :comment, :icon_data)");
        q.bindValue(":name", QString::fromStdString(link.name));
        q.bindValue(":url", QString::fromStdString(link.url));
        q.bindValue(":folder", QString::fromStdString(link.folder));
        q.bindValue(":related_url", QString::fromStdString(link.relatedUrl));
        q.bindValue(":comment", QString::fromStdString(link.comment));
        q.bindValue(":icon_data", QString::fromStdString(link.iconData));

        if (q.exec()) {
            int linkId = q.lastInsertId().toInt();
            for (const auto& ctx : link.contexts) {
                QSqlQuery cq;
                cq.prepare("INSERT INTO link_contexts (link_id, context_name) VALUES (:lid, :cname)");
                cq.bindValue(":lid", linkId);
                cq.bindValue(":cname", QString::fromStdString(ctx));
                cq.exec();
            }
        }
    }
    return true;
}

bool LinkManager::loadFromFile(const std::string& /*filePath*/) {
    m_links.clear();
    m_folders.clear();
    m_contexts.clear();

    QSqlQuery q;
    q.exec("SELECT name FROM folders");
    while(q.next()) m_folders.push_back(q.value(0).toString().toStdString());

    q.exec("SELECT name FROM contexts");
    while(q.next()) m_contexts.push_back(q.value(0).toString().toStdString());

    q.exec("SELECT id, name, url, folder, related_url, comment, icon_data FROM links");
    while(q.next()) {
        LinkData link;
        int id = q.value(0).toInt();
        link.name = q.value(1).toString().toStdString();
        link.url = q.value(2).toString().toStdString();
        link.folder = q.value(3).toString().toStdString();
        link.relatedUrl = q.value(4).toString().toStdString();
        link.comment = q.value(5).toString().toStdString();
        link.iconData = q.value(6).toString().toStdString();

        QSqlQuery cq;
        cq.prepare("SELECT context_name FROM link_contexts WHERE link_id = :id");
        cq.bindValue(":id", id);
        cq.exec();
        while(cq.next()) link.contexts.push_back(cq.value(0).toString().toStdString());

        m_links.push_back(link);
    }
    return true;
}
