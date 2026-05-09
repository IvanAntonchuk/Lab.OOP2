QT += testlib core sql network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/../LinkManagerCore

LIBS += -L$$OUT_PWD/../LinkManagerCore/debug -L$$OUT_PWD/../LinkManagerCore/release -lLinkManagerCore

HEADERS += \
    testdatabase.h \
    testlinkmanager.h \
    teststrategies.h \
    testwebutils.h

SOURCES += \
    main_test.cpp \
    testdatabase.cpp \
    testlinkmanager.cpp \
    teststrategies.cpp \
    testwebutils.cpp
