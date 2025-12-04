QT       += core gui

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
    linkmanager.cpp \
    linkserializer.cpp \
    main.cpp \
    mainwindow.cpp \
    qrcodegen.cpp \
    qrdialog.cpp \
    stb_image_impl.cpp \
    webutils.cpp

HEADERS += \
    addlinkdialog.h \
    contextmanagerdialog.h \
    exportdialog.h \
    filterdialog.h \
    foldermanagerdialog.h \
    linkmanager.h \
    linkserializer.h \
    mainwindow.h \
    qrcodegen.hpp \
    qrdialog.h \
    stb_image.h \
    webutils.h

FORMS += \
    addlinkdialog.ui \
    contextmanagerdialog.ui \
    exportdialog.ui \
    filterdialog.ui \
    foldermanagerdialog.ui \
    mainwindow.ui \
    qrdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    ../LinkManagerTest/LinkManagerTest.pro


#Lab 3: External Libraries
HEADERS += httplib.h
INCLUDEPATH += "D:/NewQt/Tools/mingw1310_64/opt/include"
LIBS += -L"D:/NewQt/Tools/mingw1310_64/opt/lib" -lws2_32 -lssl -lcrypto -lcrypt32
