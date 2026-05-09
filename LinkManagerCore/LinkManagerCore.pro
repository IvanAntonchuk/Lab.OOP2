QT += core sql network
CONFIG += c++17

TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    linkmanager.h \
    databasemanager.h \
    iexportstrategy.h \
    iimportstrategy.h \
    csvexportstrategy.h \
    csvimportstrategy.h \
    htmlexportstrategy.h \
    jsonimportstrategy.h \
    webutils.h \
    qrcodegen.hpp \
    stb_image.h

SOURCES += \
    linkmanager.cpp \
    databasemanager.cpp \
    csvexportstrategy.cpp \
    csvimportstrategy.cpp \
    htmlexportstrategy.cpp \
    jsonimportstrategy.cpp \
    webutils.cpp \
    qrcodegen.cpp \
    stb_image_impl.cpp