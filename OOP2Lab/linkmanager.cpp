#include "linkmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

LinkManager::LinkManager() {
}

void LinkManager::addLink(const LinkData& newLink) {
    m_links.push_back(newLink);
    if (!newLink.context.empty()) {
        addContext(newLink.context);
    }
}

const std::vector<LinkData>& LinkManager::getLinks() const {
    return m_links;
}

void LinkManager::deleteLink(int index) {
    if (index >= 0 && index < (int)m_links.size()) {
        m_links.erase(m_links.begin() + index);
    }
}

void LinkManager::updateLink(int index, const LinkData& updatedData) {
    if (index >= 0 && index < (int)m_links.size()) {
        m_links[index] = updatedData;
        if (!updatedData.context.empty()) {
            addContext(updatedData.context);
        }
    }
}

std::vector<LinkData> LinkManager::searchLinks(const std::string& query) const {
    std::vector<LinkData> results;
    if (query.empty()) return m_links;

    for (const auto& link : m_links) {
        if (link.name.find(query) != std::string::npos ||
            link.url.find(query) != std::string::npos ||
            link.comment.find(query) != std::string::npos ||
            link.context.find(query) != std::string::npos) {
            results.push_back(link);
        }
    }
    return results;
}

void LinkManager::addContext(const std::string& contextName) {
    if (!hasContext(contextName)) {
        m_contexts.push_back(contextName);
    }
}

const std::vector<std::string>& LinkManager::getContexts() const {
    return m_contexts;
}

void LinkManager::removeContext(const std::string& contextName) {
    auto it = std::remove(m_contexts.begin(), m_contexts.end(), contextName);
    if (it != m_contexts.end()) {
        m_contexts.erase(it, m_contexts.end());
    }
}

bool LinkManager::hasContext(const std::string& contextName) const {
    for (const auto& ctx : m_contexts) {
        if (ctx == contextName) return true;
    }
    return false;
}


bool LinkManager::saveToFile(const std::string& filePath) const {
    QJsonObject rootObject;
    QJsonArray linksArray;
    for (const auto& link : m_links) {
        QJsonObject obj;
        obj["name"] = QString::fromStdString(link.name);
        obj["url"] = QString::fromStdString(link.url);
        obj["context"] = QString::fromStdString(link.context);
        obj["comment"] = QString::fromStdString(link.comment);
        linksArray.append(obj);
    }
    rootObject["links"] = linksArray;
    QJsonArray contextsArray;
    for (const auto& ctx : m_contexts) {
        contextsArray.append(QString::fromStdString(ctx));
    }
    rootObject["contexts"] = contextsArray;
    QFile file(QString::fromStdString(filePath));
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for saving:" << QString::fromStdString(filePath);
        return false;
    }
    file.write(QJsonDocument(rootObject).toJson());
    return true;
}

bool LinkManager::loadFromFile(const std::string& filePath) {
    QFile file(QString::fromStdString(filePath));
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) return false;

    QJsonObject root = doc.object();
    m_contexts.clear();
    if (root.contains("contexts") && root["contexts"].isArray()) {
        QJsonArray ctxArray = root["contexts"].toArray();
        for (const auto& val : ctxArray) {
            m_contexts.push_back(val.toString().toStdString());
        }
    }

    m_links.clear();
    if (root.contains("links") && root["links"].isArray()) {
        QJsonArray linksArray = root["links"].toArray();
        for (const auto& val : linksArray) {
            QJsonObject obj = val.toObject();
            LinkData link;
            link.name = obj["name"].toString().toStdString();
            link.url = obj["url"].toString().toStdString();
            link.context = obj["context"].toString().toStdString();
            link.comment = obj["comment"].toString().toStdString();
            m_links.push_back(link);
        }
    }
    return true;
}
