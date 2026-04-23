QT += testlib core sql network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += "D:/UniversityGitHub/Lab.OOP2/OOP2Lab"

HEADERS += \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/linkmanager.h" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/webutils.h" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/qrcodegen.hpp" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/databasemanager.h" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/iexportstrategy.h" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/csvexportstrategy.h" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/htmlexportstrategy.h" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/iimportstrategy.h" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/csvimportstrategy.h" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/jsonimportstrategy.h" \
    testdatabase.h \
    testlinkmanager.h \
    teststrategies.h \
    testwebutils.h

SOURCES += \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/linkmanager.cpp" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/webutils.cpp" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/qrcodegen.cpp" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/databasemanager.cpp" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/csvexportstrategy.cpp" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/htmlexportstrategy.cpp" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/csvimportstrategy.cpp" \
    "D:/UniversityGitHub/Lab.OOP2/OOP2Lab/jsonimportstrategy.cpp" \
    main_test.cpp \
    testdatabase.cpp \
    testlinkmanager.cpp \
    teststrategies.cpp \
    testwebutils.cpp
