#include "linkmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

LinkManager::LinkManager() {
    addContext("Книга");
    addContext("Стаття");
    addContext("Відео");
    addContext("Вебсайт");
}

void LinkManager::addLink(const LinkData& newLink) {
    m_links.push_back(newLink);
    if (!newLink.folder.empty()) addFolder(newLink.folder);
    for (const auto& ctx : newLink.contexts) {
        if (!ctx.empty()) addContext(ctx);
    }
}

const std::vector<LinkData>& LinkManager::getLinks() const { return m_links; }

void LinkManager::deleteLink(int index) {
    if (index >= 0 && index < (int)m_links.size()) m_links.erase(m_links.begin() + index);
}

void LinkManager::updateLink(int index, const LinkData& updatedData) {
    if (index >= 0 && index < (int)m_links.size()) {
        m_links[index] = updatedData;
        if (!updatedData.folder.empty()) addFolder(updatedData.folder);

        for (const auto& ctx : updatedData.contexts) {
            if (!ctx.empty()) addContext(ctx);
        }
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
    if (!hasFolder(folderName)) m_folders.push_back(folderName);
}
const std::vector<std::string>& LinkManager::getFolders() const { return m_folders; }
void LinkManager::removeFolder(const std::string& folderName) {
    auto it = std::remove(m_folders.begin(), m_folders.end(), folderName);
    if (it != m_folders.end()) m_folders.erase(it, m_folders.end());
}
bool LinkManager::hasFolder(const std::string& folderName) const {
    for (const auto& f : m_folders) if (f == folderName) return true;
    return false;
}
void LinkManager::clearLinksFolder(const std::string& folderName) {
    for (auto& link : m_links) if (link.folder == folderName) link.folder = "";
}

void LinkManager::addContext(const std::string& contextName) {
    if (!hasContext(contextName)) m_contexts.push_back(contextName);
}
const std::vector<std::string>& LinkManager::getContexts() const { return m_contexts; }
void LinkManager::removeContext(const std::string& contextName) {
    auto it = std::remove(m_contexts.begin(), m_contexts.end(), contextName);
    if (it != m_contexts.end()) m_contexts.erase(it, m_contexts.end());
}
bool LinkManager::hasContext(const std::string& contextName) const {
    for (const auto& c : m_contexts) if (c == contextName) return true;
    return false;
}


bool LinkManager::saveToFile(const std::string& filePath) const {
    QJsonObject rootObject;
    QJsonArray linksArray;
    for (const auto& link : m_links) {
        QJsonObject obj;
        obj["name"] = QString::fromStdString(link.name);
        obj["url"] = QString::fromStdString(link.url);
        obj["folder"] = QString::fromStdString(link.folder);
        QJsonArray ctxArray;
        for (const auto& c : link.contexts) {
            ctxArray.append(QString::fromStdString(c));
        }
        obj["contexts"] = ctxArray;
        obj["relatedUrl"] = QString::fromStdString(link.relatedUrl);
        obj["comment"] = QString::fromStdString(link.comment);
        linksArray.append(obj);
    }
    rootObject["links"] = linksArray;

    QJsonArray foldersArray;
    for (const auto& f : m_folders) foldersArray.append(QString::fromStdString(f));
    rootObject["folders"] = foldersArray;

    QJsonArray contextsArray;
    for (const auto& c : m_contexts) contextsArray.append(QString::fromStdString(c));
    rootObject["contexts"] = contextsArray;

    QFile file(QString::fromStdString(filePath));
    if (!file.open(QIODevice::WriteOnly)) return false;
    file.write(QJsonDocument(rootObject).toJson());
    return true;
}

bool LinkManager::loadFromFile(const std::string& filePath) {
    QFile file(QString::fromStdString(filePath));
    if (!file.open(QIODevice::ReadOnly)) return false;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isNull()) return false;
    QJsonObject root = doc.object();

    m_folders.clear();
    if (root.contains("folders") && root["folders"].isArray()) {
        for (const auto& val : root["folders"].toArray())
            m_folders.push_back(val.toString().toStdString());
    } else if (root.contains("contexts")) {
        for (const auto& val : root["contexts"].toArray())
            m_folders.push_back(val.toString().toStdString());
    }

    m_contexts.clear();
    if (root.contains("contexts") && root["contexts"].isArray() && root.contains("folders")) {
        for (const auto& val : root["contexts"].toArray())
            m_contexts.push_back(val.toString().toStdString());
    }
    if (m_contexts.empty()) {
        addContext("Книга"); addContext("Стаття"); addContext("Відео"); addContext("Вебсайт");
    }

    m_links.clear();
    if (root.contains("links") && root["links"].isArray()) {
        for (const auto& val : root["links"].toArray()) {
            QJsonObject obj = val.toObject();
            LinkData link;

            link.name = obj["name"].toString().toStdString();
            link.url = obj["url"].toString().toStdString();

            if (obj.contains("folder")) {
                link.folder = obj["folder"].toString().toStdString();
            }

            else if (obj.contains("context") && !obj["context"].isArray()) {
                link.folder = obj["context"].toString().toStdString();
            }

            if (obj.contains("contexts") && obj["contexts"].isArray()) {
                for (const auto& val : obj["contexts"].toArray()) {
                    link.contexts.push_back(val.toString().toStdString());
                }
            }
            else if (obj.contains("context") && !obj["context"].isArray()) {
                std::string oldCtx = obj["context"].toString().toStdString();
                if (oldCtx != link.folder) {
                    link.contexts.push_back(oldCtx);
                }
            }

            if (obj.contains("relatedUrl")) {
                link.relatedUrl = obj["relatedUrl"].toString().toStdString();
            }

            link.comment = obj["comment"].toString().toStdString();
            m_links.push_back(link);
        }
    }
    return true;
}

std::vector<LinkData> LinkManager::filterLinks(const std::vector<std::string>& allowedFolders, const std::vector<std::string>& allowedContexts) const
{
    std::vector<LinkData> results;

    for (const auto& link : m_links) {
        bool folderOk = false;
        for (const auto& f : allowedFolders) {
            if (link.folder == f) {
                folderOk = true;
                break;
            }
        }

        bool contextOk = false;
        if (link.contexts.empty()) {
            for (const auto& c : allowedContexts) {
                if (c.empty()) { contextOk = true; break; }
            }
        } else {
            for (const auto& linkCtx : link.contexts) {
                for (const auto& allowed : allowedContexts) {
                    if (linkCtx == allowed) {
                        contextOk = true;
                        break;
                    }
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
