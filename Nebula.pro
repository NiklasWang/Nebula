#-------------------------------------------------
#
# Project created by QtCreator 2018-08-14T10:50:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nebula
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    utils/CQueue.cpp \
    utils/Semaphore.cpp \
    utils/SyncType.cpp \
    ui/DefaultUi.cpp \
    ui/MainWindowUi.cpp \
    ui/DeviceUi.cpp \
    core/UiComposer.cpp \
    core/MainWindow.cpp

HEADERS += \
    version.h \
    ui/UiLayout.h \
    ui/DefaultUi.h \
    ui/MainWindowUi.h \
    ui/DeviceUi.h \
    utils/clist.h \
    utils/common.h \
    utils/CQueue.h \
    utils/RWLock.h \
    utils/Semaphore.h \
    utils/SyncType.h \
    utils/TimeEx.h \
    core/MainWindow.h \
    core/UiComposer.h

FORMS += \
    ui/MainWindow.ui
