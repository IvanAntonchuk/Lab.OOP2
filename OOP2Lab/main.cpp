#include "mainwindow.h"
#include "databasemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseManager::instance().init("links.db");

    MainWindow w;
    w.show();

    return a.exec();
}
