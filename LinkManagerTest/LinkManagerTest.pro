QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += "D:/UniversityGitHub/Lab.OOP2/OOP2Lab"

HEADERS += "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/linkmanager.h"
SOURCES += "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/linkmanager.cpp"

SOURCES += tst_linkmanagertest.cpp
