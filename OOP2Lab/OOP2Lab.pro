QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addlinkdialog.cpp \
    contextmanagerdialog.cpp \
    exportdialog.cpp \
    filterdialog.cpp \
    foldermanagerdialog.cpp \
    main.cpp \
    maincontroller.cpp \
    mainwindow.cpp \
    qrdialog.cpp

HEADERS += \
    addlinkdialog.h \
    contextmanagerdialog.h \
    exportdialog.h \
    filterdialog.h \
    foldermanagerdialog.h \
    maincontroller.h \
    mainwindow.h \
    qrdialog.h

FORMS += \
    addlinkdialog.ui \
    contextmanagerdialog.ui \
    exportdialog.ui \
    filterdialog.ui \
    foldermanagerdialog.ui \
    mainwindow.ui \
    qrdialog.ui

INCLUDEPATH += $$PWD/../LinkManagerCore
LIBS += -L$$OUT_PWD/../LinkManagerCore/debug -L$$OUT_PWD/../LinkManagerCore/release -lLinkManagerCore

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#Lab 3: External Libraries
INCLUDEPATH += "D:/NewQt/Tools/mingw1310_64/opt/include"
LIBS += -L"D:/NewQt/Tools/mingw1310_64/opt/lib" -lws2_32 -lssl -lcrypto -lcrypt32
