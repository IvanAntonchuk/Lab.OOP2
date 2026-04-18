#include "maincontroller.h"
#include "mainwindow.h"
#include <QStandardPaths>
#include <QDir>

MainController::MainController(MainWindow* view) : m_view(view) {
    QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir dir(configPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    m_saveFilePath = configPath + "/links.json";
}

MainController::~MainController() {
    m_linkManager.saveToFile(m_saveFilePath.toStdString());
}

void MainController::initialize() {
    m_linkManager.loadFromFile(m_saveFilePath.toStdString());
    m_view->updateTable(m_linkManager.getLinks());
}

void MainController::addLink(const LinkData& data) {
    m_linkManager.addLink(data);
    m_view->updateTable(m_linkManager.getLinks());
}

void MainController::deleteLink(int index) {
    m_linkManager.deleteLink(index);
    m_view->updateTable(m_linkManager.getLinks());
}

void MainController::updateLink(int index, const LinkData& data) {
    m_linkManager.updateLink(index, data);
    m_view->updateTable(m_linkManager.getLinks());
}

void MainController::searchLinks(const std::string& query) {
    m_view->updateTable(m_linkManager.searchLinks(query));
}

void MainController::filterLinks(const std::vector<std::string>& folders, const std::vector<std::string>& contexts) {
    m_view->updateTable(m_linkManager.filterLinks(folders, contexts));
}

std::vector<std::string> MainController::getFolders() const {
    return m_linkManager.getFolders();
}

std::vector<std::string> MainController::getContexts() const {
    return m_linkManager.getContexts();
}

const std::vector<LinkData>& MainController::getAllLinks() const {
    return m_linkManager.getLinks();
}

LinkManager* MainController::getLinkManager() {
    return &m_linkManager;
}
