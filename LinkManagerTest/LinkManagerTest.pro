QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += "D:/UniversityGitHub/Lab.OOP2/OOP2Lab"

HEADERS += "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/linkmanager.h" \
           "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/linkserializer.h" \
           "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/webutils.h" \
           "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/qrcodegen.hpp"

SOURCES += "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/linkmanager.cpp" \
           "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/linkserializer.cpp" \
           "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/webutils.cpp" \
           "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/qrcodegen.cpp" \
           tst_linkmanagertest.cpp
