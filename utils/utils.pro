#-------------------------------------------------
#
# Project created by QtCreator 2018-09-16T13:35:38
#
#-------------------------------------------------

QT       += core

TARGET   = utils
TEMPLATE = lib
CONFIG   += staticlib

DEFINES  += UTILS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=        \
    CQueue.cpp    \
    Semaphore.cpp \
    SyncType.cpp  \
    Timer.cpp     \
    Times.cpp     \
    TimedSemaphore.cpp

HEADERS +=      \
    clist.h     \
    common.h    \
    CQueue.h    \
    RWLock.h    \
    Semaphore.h \
    SyncType.h  \
    Timer.h     \
    version.h   \
    Times.h     \
    TimedSemaphore.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SUBDIRS += \
    utils.pro
