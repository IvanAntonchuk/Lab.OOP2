QT += core testlib sql network

CONFIG += c++17 console
CONFIG -= app_bundle

INCLUDEPATH += ../OOP2Lab

SOURCES += \
    main.cpp \
    ../OOP2Lab/linkmanager.cpp \
    ../OOP2Lab/databasemanager.cpp \
    ../OOP2Lab/csvexportstrategy.cpp \
    ../OOP2Lab/webutils.cpp

HEADERS += \
    ../OOP2Lab/linkmanager.h \
    ../OOP2Lab/databasemanager.h \
    ../OOP2Lab/csvexportstrategy.h \
    ../OOP2Lab/iexportstrategy.h \
    ../OOP2Lab/webutils.h
